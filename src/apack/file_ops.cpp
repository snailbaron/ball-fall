#include "file_ops.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace {

FileInfo makeFileInfo(const fs::path& path)
{
    FileInfo info;
    info.path = path.string();
    info.baseName = path.stem.string();
    info.extension = path.extension().string();

    return info;
}

} // namespace

void forEachFile(
    const std::string& rootDirectory,
    const std::function<void(const FileInfo&)>& action)
{
    for (const auto& entry :
            fs::recursive_directory_iterator(fs::path(rootDirectory))) {
        auto fileInfo = makeFileInfo(entry.path());
        action(fileInfo);
    }
}

std::vector<uint8_t> readFile(const std::string& filePath)
{
    std::ifstream inputStream(filePath, std::ios::binary);
    return std::vector<uint8_t>(
        (std::istreambuf_iterator<char>(inputStream)),
        std::istreambuf_iterator<char>());
}
