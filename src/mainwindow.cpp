#include "mainwindow.hpp"
#include "gempyre.h"
#include "music_player.hpp"
#include "tagreader.hpp"
#include "blacklistformats.hpp"
#include <algorithm>
#include <array>
#include <bits/chrono.h>
#include <chrono>
#include <cstdlib>
#include <gempyre_client.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <gempyre_utils.h>
#include <thread>
#include <fstream>
#include <tuple>
#include <vector>
//#define ahang_debug
constexpr const std::string scale_smaller = "scale(0.85)";

mywindow::mywindow(const Filemap f,const std::string &index,const std::string &title,const int& width, const int& height):
#ifndef ahang_debug
Gempyre::Ui(f,index,title,width,height),
 #else
Gempyre::Ui(f,index,"","debug=True"),
#endif
//Gempyre::Ui(f,index,"xdg-open ",""),//fake constructor for debug purposes
//Gempyre::Ui(f,index,"librewolf ",""),//fake constructor for debug purposes
songlist(*this, "songlist"),
bgblur(*this,"background-blur"),
open_button(*this, "open"),
stop_button(*this,"stopbutton"),
play_button(*this,"playbutton"),
lightdark_button(*this,"lightdark"),
volume_slider(*this,"vol"),
seeker(*this,"seeker"),
overviewcontainer(*this,"songoverview"),
songnameinoverview(*this,"songnameinoverview"),
coverartinoverview(*this,"coverartinoverview"),
debuginfo_button(*this,"button",this->root()),
stock_coverart("song.png"),
playerbar(*this,"playerbar")
{
    debuginfo_button.set_style("position", "fixed");

    #ifdef ahang_debug
        debuginfo_button.set_html("D");
        debuginfo_button.subscribe("click", std::bind(&mywindow::on_dbginfoclicked,this));
        debuginfo_button.set_style("right", "10px");
        debuginfo_button.set_style("top", "10px");
        debuginfo_button.set_style("font-size", "1.5rem");
    #else 
        debuginfo_button.set_style("display", "none");
    #endif
    stop_button.set_html(" <img src='/stop.png' style='width:32px;height:32px'>");
    play_button.set_html(" <img src='/play.png' style='width:32px;height:32px'>");
    open_button.set_html(" <img src='/open.png' style='width:32px;height:32px'>");

    open_button.subscribe("click", std::bind(&mywindow::onopenbuttonclicked,this));
    stop_button.subscribe("click", std::bind(&mywindow::onstopclicked,this));
    play_button.subscribe("click", std::bind(&mywindow::onplaypause_clicked,this));
    volume_slider.subscribe("input", std::bind(&mywindow::onvolumesliderchanged,this,std::placeholders::_1));
    lightdark_button.subscribe("click", std::bind(&mywindow::ondarklightbtn_clicked,this,std::placeholders::_1));
    seeker.subscribe("input", std::bind(&mywindow::onuserchangedseeker,this,std::placeholders::_1));
    this->on_exit(std::bind(&std::system,"killall mpv > /dev/null"));
}


void mywindow::onopenbuttonclicked()
{
    auto dialogpath = Gempyre::Dialog::open_dir_dialog();
    if(dialogpath)
    {
        std::filesystem::path dir = dialogpath.value();
        for(auto &song : songs)std::get<0>(song)->remove();
        songs.clear();
        auto start = std::chrono::high_resolution_clock::now();
        for(const auto &entry : std::filesystem::directory_iterator(dir))
        {
            if(entry.is_regular_file() && (entry.path().filename().string()[0]!='.') && !ahang::is_blacklistformat(entry.path().extension())) 
            //if file is not a dir and not hidden and not blacklisted as non playable
            {
                songs.emplace_back(nullptr,tagreader(entry.path()),entry.path());//element - tag class - path
            }
        }
        std::ranges::sort(songs,[](auto& p,auto& s){
            return std::filesystem::last_write_time(std::get<2>(p))>std::filesystem::last_write_time(std::get<2>(s));
        });
        //TODO sort by other values;
        for(auto &song:songs)
        {
            //auto& below: Passing by reference is very important because we want to make a shared pointer. 
            //if we copy then make_shared, the pointer will be destroyed after we quit the scope.
            auto& [element,tag,filepath] = song;
            element=std::make_shared<Gempyre::Element>(*this,"div",songlist);
            element->set_attribute("class","song");
            auto title = tag.title();
            auto artist = tag.artist();
            if (artist.empty()) artist="Not Known";
            if (title.empty()) title = "Not Known";
            const std::string picsrc (tag.get_pic()?
                "data:image/png;base64, "+GempyreUtils::base64_encode(reinterpret_cast<const unsigned char*>(tag.get_pic().value()), tag.pic_size()):
                stock_coverart
            );    
            element->set_html(
            "<img src='"+picsrc+"' >"
            "<div class='songdetails'>"
                "<h3>" + title + "</h3>"
                "<p>" + artist + "</p>"
            "</div>"
            );
            element->subscribe("click", std::bind(&mywindow::ononesongentryclicked,this,song));
        }
        
        auto stop =  std::chrono::high_resolution_clock::now();
        std::cout << "indexed in: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << "ms" << std::endl;
        songs.emplace_back(std::make_shared<Gempyre::Element>(*this,"div",songlist),"","");//space at the end of the list
        std::get<0>(songs[songs.size()-1])->set_attribute("class","lastspace");
    }
}

void mywindow::ononesongentryclicked(std::tuple<std::shared_ptr<Gempyre::Element>,tagreader,std::filesystem::path> &song)
{
    auto&[element,tag,filepath] = song;
    static int lasttimerID =  0;
    
    std::system("killall mpv > /dev/null");
    
    music_player.play(filepath);//it cancels the previous song automatically if playing
    this->cancel_timer(lasttimerID);
    lasttimerID= this->start_periodic(200ms,std::bind(&mywindow::update_seeker_pos,this,std::placeholders::_1));
    const std::filesystem::path tmp = filepath;
    const auto vol = volume_slider.values()->at("value");
    std::thread mpvworkaround([this,tmp,vol]{
        std::this_thread::sleep_for(100ms);
        if(!music_player.is_active())
        {
            std::cout << "No active voice count. Maybe the file is unsopported?\nFallback to mpv:" << std::endl;
            std::system(("mpv " + GempyreUtils::qq(tmp.string()) + " --no-video --volume="+vol+" &").c_str());
            //songnameinoverview.set_style("color", "#ffd7ba");
        }
        else {
            coverartinoverview.set_style("transform", "scale(1)");// I dont think this is safe
        }
    });
    mpvworkaround.detach();
    //this will get the title from DOM (user interface) sorry if its convoluted :>
    auto title = element->children().value()[1].children().value()[0].html().value();
    songnameinoverview.set_html(title);
    if(tag.get_pic())
    {
        auto picsrc = "data:image/png;base64, "+GempyreUtils::base64_encode(reinterpret_cast<const unsigned char*>(tag.get_pic().value()), tag.pic_size());
        coverartinoverview.set_attribute("src",picsrc);
        bgblur.set_style("background-image", "url('"+picsrc+"')");
    }
    else 
    {
        coverartinoverview.set_attribute("src",stock_coverart);
        bgblur.set_style("background-image","url('"+stock_coverart+"')");
    }
}

void mywindow::onstopclicked(void)
{
    music_player.stop();
    std::system("killall mpv");
    seeker.set_attribute("value","0");
    coverartinoverview.set_style("transform", scale_smaller);
}

void mywindow::onplaypause_clicked()
{
    //std::cout << "Play/Pause: Will change MusicPlayer class instance to state: " << (!music_player.is_paused()?"PAUSE":"PLAY") << std::endl;
    music_player.toggle_pause();
    if(music_player.is_paused())coverartinoverview.set_style("transform", scale_smaller);
    else coverartinoverview.set_style("transform", "scale(1)");
    if(!music_player.is_active())
    {//that means we have a song that already has been played and we want to replay it. 
    ///If it is not the case MusicPlayer class will handle it automatically.(does nothing)
        music_player.play();
        this->start_periodic(200ms,std::bind(&mywindow::update_seeker_pos,this,std::placeholders::_1));
    }
    
}

void mywindow::update_seeker_pos(Gempyre::Ui::TimerId id)
{
    //std::cout << "Timer triggered with ID: " << id << std::endl;
    seeker.set_attribute("value",std::to_string(music_player.get_position()));
    if(!music_player.is_active())
    {
        this->cancel_timer(id);
        coverartinoverview.set_style("transform", scale_smaller);
    }
}

void mywindow::onuserchangedseeker(const Gempyre::Event & s)
{
    music_player.seek( std::stoi(s.element.values()->at("value")));
}


void mywindow::onvolumesliderchanged(const Gempyre::Event& slider_ref)
{
    auto vol = std::stof( slider_ref.element.values()->at("value"));
    music_player.set_volume(vol);
}

void mywindow::ondarklightbtn_clicked(const Gempyre::Event& e)
{
    this->toggledark(e.element.values()->at("checked")=="true");
}
void mywindow::toggledark(bool is_dark)
{
    try{
        auto body = this->root();
        //Deceleraing Gempyre Element and then distroying it makes the UI library crazy.
        if(is_dark)stock_coverart="song.png";
        else stock_coverart="song-light.png";
        //element attr light dark
        std::array<std::tuple<std::reference_wrapper<Gempyre::Element>,const std::string,const std::string,const std::string> ,11> lightcolorscheme{{
            {body,"color-scheme","light","dark"}, //Chromium does not respect user prefrence so I do.
            {body,"background","#d5d5d5",""},
            {body,"color","hsl(0deg, 0%, 21%)",""},
            {songlist,"background", "#eaeaeaa3",""},
            {bgblur,"filter","blur(40px) opacity(0.8)",""},
            {play_button,"filter","invert(1)","invert(0)"},
            {stop_button,"filter","invert(1)","invert(0)"},
            {open_button,"filter","invert(1)","invert(0)"},
            {lightdark_button, "filter","invert(1)","invert(0)"},
            {overviewcontainer,"background", "#eaeaeaa3",""},
            {coverartinoverview, "border", "1px solid #999999",""}
        }};
        for(const auto& scheme:lightcolorscheme)
        {
            auto& [e,k,lightval,darkval] = scheme;
            std::array<std::reference_wrapper<const std::string>,2> lightdark{{lightval,darkval}};
            e.get().set_style(k, lightdark[is_dark]);
        }
    }
    catch(...)
    {
        std::cerr << "some issues happend in my end. TASK: changing all widgets to " << (is_dark?"dark.":"light.") <<  std::endl;
    }
    try{
        for(auto &song:songs)
        {
            auto &[element,tag,path]=song;
            if(!tag.get_pic() && !path.empty())
            {
                element->set_html(
                "<img src='"+stock_coverart+"' >"
                "<div class='songdetails'>"
                    "<h3>" + ((!tag.title().empty())? tag.title(): std::string("Not Kown")) + "</h3>"
                    "<p>" + ((!tag.artist().empty())? tag.artist(): std::string("Not Kown")) + "</p>"
                "</div>"
                );
            }
        }

        auto src = coverartinoverview.attributes().value()["src"];
        if(src == "song.png" || src == "song-light.png")
        {
            coverartinoverview.set_attribute("src",stock_coverart);
            bgblur.set_style("background-image","url('"+stock_coverart+"')");
        }
    }
    catch(...)
    {
        std::cerr << "some issues happend in my end. TASK: song elements to " << (is_dark?"dark.":"light.") <<  std::endl;
    }
    this->eval(is_dark?"document.documentElement.style.setProperty('--song-hvr-bg-color', '');"  :
                       "document.documentElement.style.setProperty('--song-hvr-bg-color', '#d4d4d4');");
    
}

void mywindow::on_dbginfoclicked()//hidden button
{
    const auto [first_gem_ver,second_gem_ver,third_gem_ver] = Gempyre::version();
    std::cout << "-------------🚧DEBUG INFO🚧-------------" <<
    "\nGempyre version: " << first_gem_ver << '.' << second_gem_ver << '.' <<third_gem_ver <<
    "\nNumber of indexed files: " << (songs.size()==0?songs.size(): songs.size()-1)  <<
    "\nstream position: " << music_player.get_position() << '%' <<
    "\nis there any active stream? " << (music_player.is_active()?"yes":"no") <<
    "\nis stream paused? " << (music_player.is_paused()?"yes":"no") <<
    "\nis stream playing? " << (music_player.is_playing()?"yes":"no") <<
    "\n--------------------------------------\n" << std::endl;
}