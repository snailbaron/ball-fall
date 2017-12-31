#include "generator.hpp"
#include "packers.hpp"

#include <tclap/CmdLine.h>

#include <string>
#include <iostream>
#include <exception>

int main(int argc, char* argv[])
{
    try {
        TCLAP::CmdLine cmdLine("Pack resources", ' ');

        TCLAP::ValueArg<std::string> assetsPathArg(
            "a", "assets",
            "Path to assets directory",
            true, "assets", "string");
        cmdLine.add(assetsPathArg);

        TCLAP::ValueArg<std::string> outputHeaderPath(
            "", "header",
            "Path to output header file",
            true, "resources.hpp", "string");
        cmdLine.add(outputHeaderPath);

        TCLAP::ValueArg<std::string> outputDataPath(
            "", "data",
            "Path to output data file",
            true, "resources.data", "string");
        cmdLine.add(outputDataPath);

        cmdLine.parse(argc, argv);

        Generator generator(outputHeaderPath.getValue(), outputDataPath.getValue());
        packAssets(assetsPathArg.getValue(), generator);
    } catch (TCLAP::ArgException& e) {
        std::cerr << "error: " << e.error() << " for argument " << e.argId() <<
            std::endl;
    } catch (std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
}