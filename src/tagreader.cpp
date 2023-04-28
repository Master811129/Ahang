#include "tagreader.hpp"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <regex>
#include <string>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/opusfile.h>

tagreader::tagreader(const std::filesystem::path& path):
m_pic_size(0)
{
    const auto extension=path.extension();
    
    if(extension==".mp3")
    {  
        TagLib::MPEG::File mpegfile(path.c_str());
        m_title = mpegfile.tag()->title().to8Bit(true);
        m_artist=mpegfile.tag()->artist().to8Bit(true);
        auto frame = mpegfile.ID3v2Tag(true)->frameList("APIC");
        if(!frame.isEmpty())
        {
            m_album_art = ((TagLib::ID3v2::AttachedPictureFrame*)frame.front())->picture();
            m_pic_size=m_album_art.size();
        }
    }
    else if (extension==".flac") 
    {
        TagLib::FLAC::File flacfile(path.c_str());
        m_title=flacfile.tag()->title().to8Bit(true);
        m_artist=flacfile.tag()->artist().to8Bit(true);
        auto piclist=flacfile.pictureList();
        if(!piclist.isEmpty())
        {
            m_album_art = piclist[0]->data();
            m_pic_size = m_album_art.size();
        }
    }
    else if(extension==".opus")
    {
        TagLib::Ogg::Opus::File opusfile(path.c_str());
        auto tag = opusfile.tag();
        if(!tag->isEmpty())
        {
            m_title=tag->title().to8Bit(true);
            m_artist=tag->artist().to8Bit(true);
        }
        const auto& list_album_art(tag->pictureList());
        if (!list_album_art.isEmpty())
        {       
            m_album_art = list_album_art[0]->data();
            m_pic_size=m_album_art.size();
        }
    }
    else if(extension==".mkv"|extension==".avi"|extension==".wmv");//this will avoid opening those file thus improve performance
    else //this will get tag info from file automatically but wont get the photo unfortunately.
    {
        TagLib::FileRef autofile (path.string().c_str());
        auto tag=autofile.tag();
        if(tag)
        {
            m_title=autofile.tag()->title().to8Bit(true);
            m_artist=autofile.tag()->artist().to8Bit(true);
        }
    }

    if(m_title.empty())//if the music didnt have a tag at all, then I will handle this myself using the filenames.
    {
        m_title=path.filename().string();
        if(!m_title.empty()) m_title.erase(m_title.size() - path.extension().string().size());//remove extension
        auto pos = std::min(m_title.find('-'),m_title.find("—"));
        if(pos != std::string::npos)m_title.erase(pos);
    }
    //now lets block ads with modern CPP
    const std::regex adblock = std::regex("(www\\.|https://|http://)?(\\S|-)*(\\.((com)|(io)|(org)|(xyz)|(ir)|(in)|(nl)))",std::regex_constants::icase);
    m_title=std::regex_replace(m_title,adblock,"");
    m_artist=std::regex_replace(m_artist,adblock,"");
    if(m_title.find_first_not_of(" \t")==std::string::npos)m_title.clear();//if the name of the site was just ads & adblocker removed everything we endup having whitespaces.
    if(m_title.empty())m_title="Not Known";
    if(m_artist.empty())m_artist="Not Known";
}
std::string tagreader::title () const
{
    return m_title;
}

std::string tagreader::artist() const
{
    return m_artist;
}

std::optional<char *> tagreader::get_pic(void)
{
    if(m_pic_size==0)return {};
    return m_album_art.data();
}

long tagreader::pic_size() const
{
    return m_pic_size;
}