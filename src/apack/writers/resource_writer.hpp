#pragma once

#include "resources_generated.h"

#include <flatbuffers/flatbuffers.h>

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

class ResourceWriter {
public:
    ResourceWriter(const std::string& outputFile);
    ~ResourceWriter();

    void writeFont(const std::vector<uint8_t>& data);
    void writeBitmap(const std::vector<uint8_t>& data);

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
