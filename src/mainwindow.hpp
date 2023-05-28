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
    mywindow(const std::string&, const std::string&,const int,const int);
    void toggledark(bool dark);

    private:
    std::vector<std::tuple<std::shared_ptr<Gempyre::Element>, tagreader,std::filesystem::path>> songs;
    Gempyre::Element overviewcontainer;
    Gempyre::Element coverartinoverview;
    Gempyre::Element songnameinoverview;
    Gempyre::Element bgblur;
    Gempyre::Element songlist;
    Gempyre::Element open_button;
    Gempyre::Element stop_button;
    Gempyre::Element play_button;
    Gempyre::Element volume_slider;
    Gempyre::Element lightdark_button;
    Gempyre::Element about_button;

    Gempyre::Element debuginfo_button;//I make and style this in cpp file
    Gempyre::Element seeker;//that widget that seeks through the song
    Gempyre::Element playerbar;//I only add this for change its appearance

    MusicPlayer music_player;
    std::mutex mutex;
    void onopenbuttonclicked();
    void ononesongentryclicked(std::tuple<std::shared_ptr<Gempyre::Element>,tagreader,std::filesystem::path>&);
    void onstopclicked();
    void onplaypause_clicked();
    void on_dbginfoclicked();
    void update_seeker_pos (Gempyre::Ui::TimerId id);
    void onuserchangedseeker (const Gempyre::Event&);
    void onvolumesliderchanged (const Gempyre::Event& slider_ref);
    void ondarklightbtn_clicked(const Gempyre::Event& e);
    void on_aboutbtnclicked (void);
    std::string stock_coverart;//song.png song-light.png
};