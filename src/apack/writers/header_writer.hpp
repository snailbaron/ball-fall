#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

class HeaderWriter {
public:
    HeaderWriter(const std::string& outputFile);
    ~HeaderWriter();

    void add(std::string enumeration, std::string value);

private:
    std::ofstream _outFile;
    std::map<std::string, std::vector<std::string>> _enums;
};
