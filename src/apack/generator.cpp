#include "generator.hpp"

Generator::Generator(
        const std::string& outputHeader, const std::string& outputData)
    : _headerGenerator(outputHeader)
    , _resourceGenerator(outputData)
{ }

void Generator::writeFont(
    const std::string& fontId, const std::vector<uint8_t>& data)
{
    _headerGenerator.add("FontId", fontId);
    _resourceGenerator.writeFont(data);
}

void Generator::writeBitmap(
    const std::string& bitmapId, const std::vector<uint8_t>& data)
{
    _headerGenerator.add("BitmapId", bitmapId);
    _resourceGenerator.writeBitmap(data);
}