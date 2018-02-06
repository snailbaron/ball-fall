#pragma once

#include <sdl_wrapper/internal/wrapper.hpp>

#include <SDL2/SDL_render.h>

namespace sdl {

class Texture : public internal::Wrapper<SDL_Texture, SDL_DestroyTexture> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;
};

class Renderer : public internal::Wrapper<SDL_Renderer, SDL_DestroyRenderer> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;

    void clear() const
    {
        SDL_RenderClear();
    }

    void copy(
        const Texture& texture,
        const SDL_Rect& srcrect,
        const SDL_Rect& dstrect) const
    {
        SDL_RenderCopy(get(), texture.get(), &srcrect, &dstrect);
    }

    Texture createTextureFromSurface(const Surface& surface) const
    {
        return Texture(SDL_CreateTextureFromSurface(get(), surface.get());
    }

    void fillRect(const SDL_Rect& rect) const
    {
        SDL_RenderFillRect(get(), &rect);
    }

    void present() const
    {
        SDL_RenderPresent(get());
    }

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
    {
        SDL_SetRenderDrawColor(get(), r, g, b, a);
    }

    //
    // SDL_gfx
    //

    void roundedBoxRGBA(
        Sint16 x1, Sint16 y1,
        Sint16 x2, Sint16 y2,
        Sint16 rad,
        Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        roundedBoxRGBA(get(), x1, y1, x2, y2, rad, r, g, b, a);
    }
};

Texture createTextureFromSurface(
    const Renderer& renderer, const Surface& surface)
{
    return renderer.createTextureFromSurface(surface);
}

void renderClear(const Renderer& renderer)
{
    renderer.clear();
}

void renderCopy(
    const Renderer& renderer,
    const Texture& texture,
    const SDL_Rect& srcrect,
    const SDL_Rect& dstrect)
{
    renderer.copy(texture, srcrect, dstrect);
}

void renderFillRect(const Renderer& renderer, const SDL_Rect& rect)
{
    renderer.fillRect(rect);
}

void renderPresent(const Renderer& renderer)
{
    renderer.present();
}

void setRenderDrawColor(
    const Renderer& renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    renderer.setDrawColor(r, g, b, a);
}

} // namespace sdl