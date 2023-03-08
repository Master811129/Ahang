#pragma once
#include "soloud_wavstream.h"
#include <soloud.h>
#include <string>
#include <filesystem>
#include <optional>

class MusicPlayer
{
    public:
    MusicPlayer();
    ~MusicPlayer();

    void play(const std::filesystem::path & path);
    void play();//for replaying
    void toggle_pause();
    void stop();
    bool is_playing();
    bool is_paused();
    bool is_active();
    float get_position();
    void seek(float precent);
    void set_volume (float vol);

    private:
    SoLoud::Soloud engine;
    SoLoud::WavStream stream;
    std::optional<int> stream_handle;
};