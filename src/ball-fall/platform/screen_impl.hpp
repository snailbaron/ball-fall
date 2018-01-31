#pragma once

#include <platform/screen.hpp>

#include <SDL2/SDL.h>

namespace platform {

class ScreenImpl : public Screen {
public:
    ScreenImpl();
    ~ScreenImpl();

    void clear(const Color& color) override;

    void drawRoundedBox(
        const Vector<int16_t>& position,
        const Vector<int16_t>& size,
        int16_t cornerRadius,
        const Color& color) override;

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
};

} // namespace platform
