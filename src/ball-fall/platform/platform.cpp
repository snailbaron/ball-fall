#include "static_platform.hpp"
#include "resources.hpp"

#include <platform.hpp>
#include <config.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <cassert>
#include <stdexcept>
#include <memory>

using static_platform::window;
using static_platform::renderer;
using static_platform::resources;

namespace platform {

void init()
{
    static_platform::init();
}

void kill()
{
    static_platform::kill();
}

} // namespace platform

namespace resource {

std::shared_ptr<Font> font(res::FontId fontId, int ptSize)
{
    return resources()->font(fontId, ptSize);
}

std::shared_ptr<Texture> texture(res::BitmapId bitmapId)
{
    return resources()->texture(bitmapId);
}

std::shared_ptr<Texture> textTexture(
    const std::string& text,
    res::FontId font,
    const Color& textColor,
    const Color& bgColor,
    const Vector<int>& desiredSize)
{
    int height = desiredSize.y;
    TTF_Font* fontPtr = resources()->font(font, height);
    int width;
    TTF_SizeUTF8(fontPtr, text.c_str(), &width, nullptr);
    while (width > desiredSize.x) {
        height = height * desiredSize.x / width;
        fontPtr = resources()->font(font, height);
        TTF_SizeUTF8(fontPtr, text.c_str(), &width, nullptr);
    }

    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        fontPtr,
        text.c_str(),
        sdlColor(textColor),
        sdlColor(bgColor));
    Texture texture(
        surface->w,
        surface->h,
        SDL_CreateTextureFromSurface(renderer(), surface));
    SDL_FreeSurface(surface);

    return texture;
}

} // namespace resource


} // namespace screen