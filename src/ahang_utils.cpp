#include "ahang_utils.hpp"
#include <cstdlib>
#include <filesystem>
#include <array>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define WINDOWS
#include <Windows.h>
#endif
bool ahang::is_blacklistformat(const std::filesystem::path &extension) noexcept
{
    const std::array blacklistformats {
        //common image formats
        ".png",
        ".jpg",".JPG",".jpeg",
        ".gif",
        ".svg",
        //config/system files
        ".conf",
        ".ini",
        ".inf",
        ".db",
        //archive files
        ".zip",
        ".gz",
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

int ahang::system(const std::string& command)//stub for new system()
{
    #ifdef WINDOWS
    
        STARTUPINFO info={sizeof(info)};
		PROCESS_INFORMATION processInfo;
		if (CreateProcess(nullptr, const_cast<char*>(command.c_str()), nullptr, nullptr, TRUE,CREATE_NO_WINDOW, nullptr, nullptr, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
        return 0;
    #else
    return std::system(command.c_str());
    #endif
}