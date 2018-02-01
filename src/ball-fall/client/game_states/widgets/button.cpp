#include "button.hpp"
#include <platform.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <utility>

const std::map<Widget::VisualState, Color> Button::BgColorMap {
    { VisualState::Normal,  Color(255, 255, 200) },
    { VisualState::Focused, Color(200, 255, 180) },
    { VisualState::Pressed, Color(250, 200, 100) },
};

void Button::size(int width, int height)
{
    auto sizeVector = Vector<int>(width, height);
    if (_size != sizeVector) {
        _size = sizeVector;
        recalculateTexture();
    }
}

Button& Button::text(std::string text)
{
    if (text != _text) {
        _text = std::move(text);
        recalculateTexture();
    }
    return *this;
}

Button& Button::action(std::function<void()> action)
{
    _action = std::move(action);
    return *this;
}

void Button::render() const
{
    platform::screen().drawRect(_position, _size, BorderColor);
    platform::screen().drawRect(
        _position + Vector<int>{BorderSize, BorderSize},
        _size - Vector<int>{2 * BorderSize, 2 * BorderSize},
        _bgColor);
    platform::screen().drawTexture(
        _position + Vector<int>{2 * BorderSize, 2 * BorderSize},
        _texture);
}

void Button::update(double /*delta*/)
{
}

bool Button::contains(int x, int y)
{
    return x >= _position.x && x < _position.x + _size.x &&
        y >= _position.y && y < _position.y + _size.y;
}

void Button::onVisualState(VisualState state)
{
    _bgColor = BgColorMap.at(state);
    recalculateTexture();
}

void Button::onActivate()
{
    _action();
}

void Button::recalculateTexture()
{
    _texture = platform::screen().textTexture(
        _text,
        Font,
        Color{0, 0, 0},
        _bgColor,
        {_size.x - 2 * BorderSize, _size.y - 2 * BorderSize});
}
