#pragma once

#include "types.hpp"
#include "vector.hpp"

#include <sdl_wrapper.hpp>

class Screen {
public:
    struct Config {
        Config();

        std::string title;
        int width;
        int height;
    };

    Screen(const Config& config = Config());
    ~Screen();

    void show();

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

    void drawImage(const Vector<int>& position, const Image& image);

private:
    sdl::Window _window;
    sdl::Renderer _renderer;
};
