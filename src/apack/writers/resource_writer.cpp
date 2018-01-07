#include "resource_writer.hpp"
#include "../file_ops.hpp"

namespace flat = BallFall::Resources;

ResourceWriter::ResourceWriter(const std::string& outputFile)
    : _outFile(outputFile, std::ios::binary)
{ }

ResourceWriter::~ResourceWriter()
{
    auto fontVector = _builder.CreateVector(_fonts);
    auto bitmapVector = _builder.CreateVector(_bitmaps);

    auto resources = flat::CreateResources(_builder, fontVector, bitmapVector);

    flat::FinishResourcesBuffer(_builder, resources);

    _outFile.write(
        reinterpret_cast<char*>(_builder.GetBufferPointer()),
        _builder.GetSize());
}

void ResourceWriter::writeFont(const std::vector<uint8_t>& data)
{
    auto vec = _builder.CreateVector(data);
    _fonts.push_back(flat::CreateFont(_builder, vec));
}

void ResourceWriter::writeBitmap(const std::vector<uint8_t>& data)
{
    auto vec = _builder.CreateVector(data);
    _bitmaps.push_back(flat::CreateBitmap(_builder, 32, 32, vec));
}
