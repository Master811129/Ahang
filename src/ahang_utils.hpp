#pragma once
#include <filesystem>
#include <string>
#include <optional>
namespace ahang {
    bool is_supported (const std::filesystem::path &) noexcept;
    int system (const std::string& e);
    void open_link (const std::string link);
    std::optional<std::filesystem::path> get_os_music_path ();
}