#pragma once

#include <sdl_wrapper/internal/wrapper.hpp>
#include <sdl_wrapper/surface.hpp>

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <tuple>

namespace sdl {
namespace ttf {

void init()
{
    TTF_Init();
}

void quit()
{
    TTF_Quit();
}

class Font : public internal::Wrapper<TTF_Font, TTF_CloseFont> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;

    std::tuple<int, int> sizeUtf8(const std::string& text) const
    {
        std::tuple<int, int> result;
        TTF_SizeUTF8(
            get(), text.c_str(), std::get<0>(result), std::get<1>(result));
        return result;
    }

    Surface renderUtf8Solid(const std::string& text, const SDL_Color& fg) const
    {
        return Surface(TTF_RenderUTF8_Solid(get(), text.c_str(), fg));
    }

    Surface renderUtf8Shaded(
        const std::string& text, const SDL_Color& fg, const SDL_Color& bg) const
    {
        return Surface(TTF_RenderUTF8_Shaded(get(), text.c_str(), fg, bg));
    }

    Surface renderUtf8Blended(
        const std::string& text, const SDL_Color& fg) const
    {
        return Surface(TTF_RenderUTF8_Blended(get(), text.c_str(), fg));
    }
};

Font openFont(const std::string& file, int ptSize)
{
    return Font(TTF_OpenFont(file.c_str(), ptSize));
}

std::tuple<int, int> sizeUtf8(const Font& font, const std::string& text)
{
    return font.sizeUtf8(text);
}

Surface renderUtf8Solid(
    const Font& font, const std::string& text, const SDL_Color& fg)
{
    return font.renderUtf8Solid(text, fg);
}

Surface renderUtf8Shaded(
    const Font& font,
    const std::string& text,
    const SDL_Color& fg,
    const SDL_Color& bg)
{
    return font.renderUtf8Shaded(text, fg, bg);
}

Surface renderUtf8Blended(
    const Font& font, const std::string& text, const SDL_Color& fg)
{
    return font.renderUtf8Blended(text, fg);
}

}} // namespace sdl::ttf