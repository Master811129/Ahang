#pragma once
#include <filesystem>
#include <gempyre.h>
#include <memory>
#include <string>
#include <vector>
#include <soloud.h>
#include "music_player.hpp"
#include <tuple>
#include "tagreader.hpp"

class mywindow:
public Gempyre::Ui
{
    public:
    mywindow(const Gempyre::Ui::Filemap,const std::string&, const std::string&,const int&,const int&);
    Gempyre::Element coverartinoverview;
    Gempyre::Element bgblur;
    private:
    
    std::vector<std::tuple<std::shared_ptr<Gempyre::Element>, tagreader,std::filesystem::path>> songs;
    Gempyre::Element songlist;
    Gempyre::Element open_button;
    Gempyre::Element stop_button;
    Gempyre::Element play_button;
    Gempyre::Element volume_slider;
    Gempyre::Element lightdark_button;

    Gempyre::Element songnameinoverview;
    Gempyre::Element debuginfo_button;//I make this dinamically in cpp file
    Gempyre::Element seeker;//that widget that seeks through the song
    Gempyre::Element playerbar;//I only add this for change its appearance
    //Gempyre::Element songoverview;

    MusicPlayer music_player;

    void onopenbuttonclicked();
    void ononesongentryclicked(std::tuple<std::shared_ptr<Gempyre::Element>,tagreader,std::filesystem::path>&);
    void onstopclicked();
    void onplaypause_clicked();
    void on_dbginfoclicked(const Gempyre::Event &clickedsong);
    void update_seeker_pos (Gempyre::Ui::TimerId id);
    void onvolumesliderchanged (const Gempyre::Event& slider_ref);
    void ondarklightbtn_clicked(const Gempyre::Event& e);
    void toggledark(bool dark);
    std::string stock_coverart;//song.png song-light.png
};