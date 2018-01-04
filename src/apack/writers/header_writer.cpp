#include "header_writer.hpp"

HeaderWriter::HeaderWriter(const std::string& outputFile)
    : _outFile(outputFile, std::ios::binary)
{
}

HeaderWriter::~HeaderWriter()
{
    _outFile <<
        "#pragma once\n\n" <<
        "#include <cstdint>\n\n" <<
        "namespace res {\n";

    for (const auto& enumValuesPair : _enums) {
        const auto& enumeration = enumValuesPair.first;
        const auto& values = enumValuesPair.second;

        _outFile << "\nenum class " << enumeration << " : uint32_t {\n";
        for (const auto& value : values) {
            _outFile << "    " << value << ",\n";
        }
        _outFile << "};\n";
    }

    _outFile << "\n\n} // namespace res   fapfap \n";
}

void HeaderWriter::add(std::string enumeration, std::string value)
{
    _enums[std::move(enumeration)].push_back(std::move(value));
}
