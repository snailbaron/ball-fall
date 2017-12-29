#include "resources_generated.h"

#include <tclap/CmdLine.h>
#include <zlib.h>

#include <iostream>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <cstdint>
#include <fstream>

namespace fs = std::experimental::filesystem;
namespace flat = BallFall::Resources;

std::string fontIdByFileName(std::string fileName)
{
    std::transform(fileName.begin(), fileName.end(), fileName.begin(),
        [] (unsigned char c) {
            if (c == '-') {
                return '_';
            }
            return static_cast<char>(std::toupper(c));
        });

    return fileName;
}

int main(int argc, char* argv[])
{
    TCLAP::ValueArg<std::string> assetsPathArg(
        "a", "assets",
        "Path to assets directory",
        true, "assets", "string");
    TCLAP::ValueArg<std::string> outputHeaderPath(
        "", "header",
        "Path to output header file",
        true, "resources.hpp", "string");
    TCLAP::ValueArg<std::string> outputDataPath(
        "", "data",
        "Path to output data file",
        true, "resources.data", "string");

    try {
        TCLAP::CmdLine cmdLine("Pack resources", ' ');
        cmdLine.add(assetsPathArg);
        cmdLine.add(outputHeaderPath);
        cmdLine.add(outputDataPath);
        cmdLine.parse(argc, argv);
    } catch (TCLAP::ArgException& e) {
        std::cerr << "error: " << e.error() << " for argument " << e.argId() <<
            std::endl;
    }

    fs::path assetsPath = assetsPathArg.getValue();
    fs::path fontsPath = assetsPath / "fonts";

    std::ofstream outStream(outputHeaderPath.getValue());
    outStream <<
        "#pragma once\n\n" <<
        "namespace res {\n\n" <<
        "enum class FontId {\n";

    flatbuffers::FlatBufferBuilder builder;
    std::vector<flatbuffers::Offset<flat::Font>> fonts;

    size_t fondIndex = 0;
    std::cout << "path: " << fontsPath << std::endl;
    for (auto& entry : fs::recursive_directory_iterator(fontsPath)) {
        std::cout << "entry: " << entry.path() << std::endl;

        if (entry.path().extension().string() != ".ttf") {
            continue;
        }

        auto fontFilePath = entry.path();
        auto fontFileName = fontFilePath.stem().string();
        auto fontId = fontIdByFileName(fontFileName);

        outStream << "    " << fontId << ",\n";

        std::ifstream fontFileStream(fontFilePath.string(), std::ios::binary);
        std::vector<uint8_t> fontFileContent(
            (std::istreambuf_iterator<char>(fontFileStream)),
            std::istreambuf_iterator<char>());

        auto fontData = builder.CreateVector(fontFileContent);
        fonts.push_back(flat::CreateFont(builder, fontData));
    }

    outStream << "};\n\n} // namespace res\n";

    auto fontVector = builder.CreateVector(fonts);
    auto resources = flat::CreateResources(builder, fontVector);

    builder.Finish(resources);

    std::ofstream packedStream(outputDataPath.getValue());
    packedStream.write(
        reinterpret_cast<char*>(builder.GetBufferPointer()),
        builder.GetSize());
}