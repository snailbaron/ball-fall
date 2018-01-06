#pragma once

#include <string>
#include <functional>
#include <vector>
#include <cstdint>

struct FileInfo {
    std::string path;
    std::string baseName;
    std::string extension;
};

void forEachFile(
    const std::string& rootDirectory,
    const std::function<void(const FileInfo&)>& action);
