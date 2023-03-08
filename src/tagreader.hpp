#pragma once
#include <taglib/tbytevector.h>
#include <tuple>
#include <optional>
#include <string>
#include <memory>
#include <filesystem>
#include <taglib/tag.h>
#include <taglib/taglib.h>
#include <taglib/id3v2.h>
#include <taglib/mpegfile.h>
#include <taglib/asffile.h>
#include <taglib/flacfile.h>
#include <taglib/fileref.h>

class tagreader
{
    public:
    tagreader(const std::filesystem::path&);
    std::string title() const;
    std::string artist() const;
    std::optional<char *> get_pic(void);
    long pic_size () const;
    private:
    std::string m_title;
    std::string m_artist;
    TagLib::ByteVector m_album_art;
    long m_pic_size;
};