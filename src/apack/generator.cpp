#include "generator.hpp"

Generator::Generator(
        const std::string& outputHeader, const std::string& outputData)
    : _headerGenerator(outputHeader)
    , _resourceGenerator(outputData)
{ }

void Generator::addFont(
    const std::string& fontId, const std::vector<uint8_t>& data)
{
    _headerGenerator.add("FontId", fontId);
    _resourceGenerator.addFont(data);
}

void Generator::addBitmap(
    const std::string& bitmapId, const std::vector<uint8_t>& data)
{
    _headerGenerator.add("BitmapId", bitmapId);
    _resourceGenerator.addBitmap(data);
}