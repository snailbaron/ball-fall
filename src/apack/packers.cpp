#include "packers.hpp"
#include "file_ops.hpp"

#include <cctype>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace {

using PackFile = std::function<void(const FileInfo&, Generator&)>;

std::string toCamelCase(std::string source)
{
    auto isSeparator = [](int ch) {
        return std::isspace(ch) || ch == '-' || ch == '_';
    };

    std::ostringstream output;
    bool capitalize = true;
    for (char ch : source) {
        if (isSeparator(ch)) {
            capitalize = true;
            continue;
        }

        output << capitalize ? std::toupper(ch) : ch;
        capitalize = false;
    }

    return output.str();
}


PackFile packByExtension(const std::string& extension, const PackFile& pack)
{
    return [&extension, &pack] (const FileInfo& info, Generator& generator) {
        if (info.extension != extension) {
            return;
        }
        return pack(info, generator);
    };
}

std::vector<PackFile> g_packers {
    packByExtension(".ttf", [] (const FileInfo& info, Generator& generator) {
        auto fontId = toCamelCase(info.baseName);
        auto fontFileContent = readFile(info.path);
        generator.addFont(fontId, fontFileContent);
    }),

    packByExtension(".png", [] (const FileInfo& info, Generator& generator) {
        auto bitmapId = toCamelCase(info.baseName);
        auto bitmapFileContent = readFile(info.path);
        generator.addBitmap(bitmapId, bitmapFileContent);
    }),
};

} // namespace

void packAssets(const std::string& assetDir, Generator& generator)
{
    forEachFile(
        assetDir,
        [&generator] (const FileInfo& fileInfo) {
            for (const auto& packer : g_packers) {
                packer(fileInfo, generator);
        }
    });
}
