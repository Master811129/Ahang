#include "blacklistformats.hpp"
#include <filesystem>
#include <array>

bool ahang::is_blacklistformat(const std::filesystem::path &extension) noexcept
{
    const std::array blacklistformats {
        //common image formats
        ".png",
        ".jpg",".JPG",".jpeg",
        ".gif",
        ".svg",
        //config files
        ".conf",
        ".ini",
        ".inf",
        //archive files
        ".zip",
        ".gz"
        ".rar",
        ".exe",
        //doc files
        ".pdf",
        ".ppt",".pptx",".doc",".docx",".xls",".xlsx",//MS-office
        ".txt",
        ".odt",
        ".html",
    };
    for(const auto& f:blacklistformats)if(extension==f)return true;
    return false;
}