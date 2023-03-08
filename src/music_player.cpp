#include "music_player.hpp"
#include  <iostream>
MusicPlayer::MusicPlayer()
{
    std::cout << "initializing Soload\n";
    engine.init();
    std::cout << "done" << std::endl;
}

MusicPlayer::~MusicPlayer()
{
    engine.deinit();
}

void MusicPlayer::play(const std::filesystem::path &music_path)
{
    engine.stopAll();
    stream.load(music_path.c_str());
    this->play();
}
void MusicPlayer::play()
{
    if(stream.mFilename==nullptr)return;
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


void MusicPlayer::seek(float precent_value)
{
    //TODO
}

void MusicPlayer::set_volume(float vol_precent)
{
    engine.setGlobalVolume(vol_precent/100);
}