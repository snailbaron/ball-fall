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

namespace screen {

void show()
{
    SDL_ShowWindow(window());
}

void clear(const Color& color)
{
    SDL_SetRenderDrawColor(renderer(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer());
}

void present()
{
    SDL_RenderPresent(renderer());
}

void drawRect(
    const Vector<int>& position, const Vector<int>& size, const Color& color)
{
    SDL_SetRenderDrawColor(renderer(), color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, size.x, size.y};
    SDL_RenderFillRect(renderer(), &rect);
}

void drawRoundedBox(
    const Vector<int16_t>& position,
    const Vector<int16_t>& size,
    int16_t cornerRadius,
    const Color& color)
{
    int result = roundedBoxRGBA(
        renderer(),
        position.x, position.y, position.x + size.x, position.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
    assert(result == 0);
}

void drawTexture(
    const Vector<int>& position,
    const std::shared_ptr<Texture>& texture)
{
    SDL_Rect dstRect {
        position.x,
        position.y,
        position.x + texture.width,
        position.y + texture.height
    };

    auto textureImpl = std::static_pointer_cast<TextureImpl>(texture);
    SDL_RenderCopy(renderer(), textureImpl->raw(), nullptr, &dstRect);
}

} // namespace screen