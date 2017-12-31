#pragma once

#include <flatbuffers/flatbuffers.h>
#include "resources_generated.h"

#include <string>
#include <vector>
#include <fstream>

class ResourceWriter {
public:
    ResourceWriter(const std::string& outputFile);
    ~ResourceWriter();

    void addFont(const std::vector<uint8_t>& data);
    void addBitmap(const std::vector<uint8_t>& data);

private:
    std::ofstream _outFile;
    flatbuffers::FlatBufferBuilder _builder;
    std::vector<flatbuffers::Offset<BallFall::Resources::Font>> _fonts;
    std::vector<flatbuffers::Offset<BallFall::Resources::Bitmap>> _bitmaps;
};

struct DataLocation {
    const uint8_t* ptr;
    uint32_t size;
};

class ResourceReader {
public:
    ResourceReader(const std::string& inputFile);

    DataLocation font(uint32_t fontId);
    DataLocation bitmap(uint32_t bitmapId);

private:
    const BallFall::Resources::Resources* _resources;
};