#include "ahang_utils.hpp"
#include <filesystem>
#include <array>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define WINDOWS
#include <Windows.h>
#endif

bool ahang::is_supported(const std::filesystem::path &filepath) noexcept//TODO
{
    const auto name = filepath.filename();
    const auto extension = filepath.extension();
    const std::array whitelist_extensions {".mp3",".flac",".FLAC",".opus",".aac",".amr",".alac",".wav"};
    for(const auto& f:whitelist_extensions)if(extension==f)return true;
    return false;
}

int ahang::system(const std::string& command)
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