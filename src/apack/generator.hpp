#pragma once

#include "header_generator.hpp"
#include "resource_generator.hpp"

#include <string>
#include <vector>

class Generator {
public:
    Generator(const std::string& outputHeader, const std::string& outputData);

    void addFont(const std::string& fontId, const std::vector<uint8_t>& data);
    void addBitmap(
        const std::string& bitmapId, const std::vector<uint8_t>& data);

private:
    HeaderWriter _headerGenerator;
    ResourceWriter _resourceGenerator;
};