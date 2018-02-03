#pragma once

#include "sdl_ttf_library_impl.hpp"

#include <sdl_wrapper/font.hpp>

#include <memory>

namespace sdl {
namespace ttf {

class FontImpl : public Font {
public:
    FontImpl(std::shared_ptr<Library> ttfLibrary, TTF_Font* font);

    std::shared_ptr<Surface> renderUtf8Solid(
        const std::string& text, const SDL_Color& fg) const override;

    std::shared_ptr<Surface> renderUtf8Shaded(
        const std::string& text,
        const SDL_Color& fg,
        const SDL_Color& bg) const override;

    std::shared_ptr<Surface> renderUtf8Blended(
        const std::string& text, const SDL_Color& fg) const override;

private:
    std::shared_ptr<LibraryImpl> _ttfLibrary;
    std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> _font;
};

}} // namespace sdl::ttf
