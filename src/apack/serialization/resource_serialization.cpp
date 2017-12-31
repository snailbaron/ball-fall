#include "resource_serialization.hpp"
#include "../file_ops.hpp"

namespace flat = BallFall::Resources;

ResourceWriter::ResourceWriter(const std::string& outputFile)
    : _outFile(outputFile, std::ios::binary)
{ }

ResourceWriter::~ResourceWriter()
{
    auto fontVector = _builder.CreateVector(_fonts);
    auto resources = flat::CreateResources(_builder, fontVector);

    _builder.Finish(resources);

    _outFile.write(
        reinterpret_cast<char*>(_builder.GetBufferPointer()),
        _builder.GetSize());
}

void ResourceWriter::addFont(const std::vector<uint8_t>& data)
{
    auto vec = _builder.CreateVector(data);
    _fonts.push_back(flat::CreateFont(_builder, vec));
}

void ResourceWriter::addBitmap(const std::vector<uint8_t>& data)
{
    auto vec = _builder.CreateVector(data);
    _bitmaps.push_back(flat::CreateBitmap(_builder, 32, 32, vec));
}

ResourceReader::ResourceReader(const std::string& inputFile)
{
    auto inputData = readFile(inputFile);
    _resources = flat::GetResources(inputData.data());
}

DataLocation ResourceReader::font(uint32_t fontId)
{
    auto font = (*_resources->fonts())[fontId];
    return {font->data()->data(), font->data()->size()};
}

DataLocation ResourceReader::bitmap(uint32_t bitmapId)
{
    auto bitmap = (*_resources->bitmaps())[bitmapId];

}