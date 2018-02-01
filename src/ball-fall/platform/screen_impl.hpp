#pragma once

#include <platform/screen.hpp>

#include <SDL2/SDL.h>

class ScreenImpl : public Screen {
public:
    ScreenImpl();
    ~ScreenImpl();

    void show() override;
    void clear(const Color& color) override;
    void present() override;

    void drawRect(
        const Vector<int>& position,
        const Vector<int>& size,
        const Color& color) override;
    void drawRoundedBox(
        const Vector<int16_t>& position,
        const Vector<int16_t>& size,
        int16_t cornerRadius,
        const Color& color) override;
    void drawTexture(
        const Vector<int>& position,
        const Texture& texture) override;

    Texture textTexture(
        const std::string& text,
        res::FontId font,
        const Color& textColor,
        const Color& bgColor,
        const Vector<int>& desiredSize) override;

    // TODO: remove
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
};
