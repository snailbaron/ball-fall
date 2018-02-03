#pragma once

#include <sdl_wrapper/surface.hpp>

#include <string>

namespace sdl {
namespace ttf {

class Font {
public:
    virtual ~Font() {}

    virtual std::shared_ptr<Surface> renderUtf8Solid(
        const std::string& text, const SDL_Color& fg) const = 0;

    virtual std::shared_ptr<Surface> renderUtf8Shaded(
        const std::string& text,
        const SDL_Color& fg,
        const SDL_Color& bg) const = 0;

    virtual std::shared_ptr<Surface> renderUtf8Blended(
        const std::string& text, const SDL_Color& fg) const = 0;
};

}} // namespace sdl::ttf
