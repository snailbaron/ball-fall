#include <util.hpp>

#include <fstream>

namespace util {

std::vector<uint8_t> readFile(const std::string& filePath)
{
    std::ifstream inputStream(filePath, std::ios::binary);
    return std::vector<uint8_t>(
        (std::istreambuf_iterator<char>(inputStream)),
        std::istreambuf_iterator<char>());
}

} // namespace util
