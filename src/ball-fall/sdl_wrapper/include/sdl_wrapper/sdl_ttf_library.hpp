#pragma once

#include <sdl_wrapper/font.hpp>

#include <memory>
#include <string>

namespace sdl {
namespace ttf {

class Library {
public:
    virtual ~Library() {}

    virtual std::shared_ptr<Font> openFont(
        const std::string& file, int ptSize) const = 0;
};

}} // namespace sdl::img