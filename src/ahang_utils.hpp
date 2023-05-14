#pragma once
#include <filesystem>
#include <string>
namespace ahang {
    bool is_supported (const std::filesystem::path &) noexcept;
    int system (const std::string& e);
}