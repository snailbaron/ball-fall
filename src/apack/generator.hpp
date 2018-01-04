#pragma once

#include "writers/header_writer.hpp"
#include "writers/resource_writer.hpp"

#include <string>
#include <vector>

class Generator {
public:
    Generator(const std::string& outputHeader, const std::string& outputData);

    void writeFont(const std::string& fontId, const std::vector<uint8_t>& data);
    void writeBitmap(
        const std::string& bitmapId, const std::vector<uint8_t>& data);

private:
    HeaderWriter _headerGenerator;
    ResourceWriter _resourceGenerator;
};