#include "music_player.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <soloud.h>


MusicPlayer::MusicPlayer():
stream_handle({})
{
    std::cout << "initializing Soload\r" << std::flush;
    auto result_init = engine.init();
    std::cout << "✅Soload initialized with code: "<< result_init;
    if(result_init==0)std::cout << " | Backed: " << engine.getBackendString() << std::endl;
    else std::cout << std::endl;
}

MusicPlayer::~MusicPlayer()
{
    engine.deinit();
}

void MusicPlayer::play(const std::filesystem::path &music_path)
{
    engine.stopAll();
    stream.load(music_path.string().c_str());
    this->play();
    m_path = music_path;
}

void MusicPlayer::play()
{
    //if(stream.mFilename==nullptr)return;
    engine.stopAll();
    stream_handle = engine.play(stream);
}


bool MusicPlayer::is_playing()
{
    if(!stream_handle)return false;
    return engine.getActiveVoiceCount()!=0;
}

bool MusicPlayer::is_paused()
{
    if(!stream_handle)return false;
    return engine.getPause(stream_handle.value());
}

bool MusicPlayer::is_active()
{
    if(!stream_handle)return false;
    return engine.getPause(stream_handle.value())||engine.getActiveVoiceCount()!=0;
}

void MusicPlayer::toggle_pause()
{
    if(this->is_playing()){
        engine.setPauseAll(true);
        return;
    }
    engine.setPauseAll(false);
}

void MusicPlayer::stop()
{
    engine.stopAll();
}

float MusicPlayer::get_position()
{
    if(!stream_handle)return 0;
    auto pos = engine.getStreamPosition(stream_handle.value());
    auto length = stream.getLength();
    if(pos==0|length==0)return 0;
    return pos*100/length;
}

const std::optional<std::filesystem::path> MusicPlayer::path() const
{
    if(m_path) return m_path;
    return {};
}

void MusicPlayer::seek(float precent_value)
{
    if(!stream_handle)return;;
    engine.seek(stream_handle.value(), stream.getLength() * (precent_value*0.01));
}

void MusicPlayer::set_volume(float vol_precent)
{
    engine.setGlobalVolume(vol_precent/100);
}

const SoLoud::Soloud* MusicPlayer::pass_engine () 
{
    return &engine;
}