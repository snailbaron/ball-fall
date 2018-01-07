#pragma once

#include "widget.hpp"
#include "color.hpp"
#include "vector.hpp"
#include "resources.hpp"

#include <cstdint>
#include <string>

class SolidBackground : public Widget {
public:
    using Widget::Widget;

    SolidBackground& color(const Color& color);

    void render() const override;

private:
    Color _color = Color::Black;
};

class Button : public Widget {
public:
    using Widget::Widget;

    Button& position(int x, int y);
    Button& size(int width, int height);
    Button& text(std::string text);

    void render() const override;
private:
    void recalculateTexture();

    static constexpr auto BorderSize = 5;
    static constexpr auto BorderColor = Color(100, 50, 50);
    static constexpr auto BgColor = Color(150, 150, 100);
    static constexpr auto Font = res::FontId::Mecha;

    Vector<int> _position;
    Vector<int> _size;
    std::string _text;

    SDL_Texture* _texture = nullptr;
    Vector<int> _textureSize;
};