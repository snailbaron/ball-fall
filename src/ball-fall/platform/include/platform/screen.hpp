#pragma once

#include <platform/types.hpp>
#include <platform/vector.hpp>

#include <sdl_wrapper.hpp>
#include <string>

class Screen {
public:
    Screen(sdl::Renderer renderer);

    void clear(const Color& color);
    void present();

    void drawRect(
        const Vector<int>& position,
        const Vector<int>& size,
        const Color& color);

    void drawRoundedBox(
        const Vector<int16_t>& position,
        const Vector<int16_t>& size,
        int16_t cornerRadius,
        const Color& color);

    void drawSprite(const Vector<int>& position, const Sprite& sprite);

private:
    sdl::Renderer _renderer;
};
