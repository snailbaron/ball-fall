#include "button.hpp"
#include "../../media.hpp"
#include "../../resources.hpp"

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
    SDL_SetRenderDrawColor(
        media::renderer(), BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
    SDL_Rect outerRect {_position.x, _position.y, _size.x, _size.y};
    SDL_RenderFillRect(media::renderer(), &outerRect);

    SDL_SetRenderDrawColor(
        media::renderer(), _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
    SDL_Rect innerRect {
        outerRect.x + BorderSize,
        outerRect.y + BorderSize,
        outerRect.w - 2 * BorderSize,
        outerRect.h - 2 * BorderSize};
    SDL_RenderFillRect(media::renderer(), &innerRect);

    SDL_Rect dstRect {
        innerRect.x + (innerRect.w - _textureSize.x) / 2,
        innerRect.y + (innerRect.h - _textureSize.y) / 2,
        _textureSize.x,
        _textureSize.y};

    if (_texture) {
        SDL_RenderCopy(media::renderer(), _texture, nullptr, &dstRect);
    }
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
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    const int targetWidth = _size.x - 2 * BorderSize;

    int height = _size.y - 2 * BorderSize;
    TTF_Font* font = resources::font(Font, height);
    int width;
    TTF_SizeUTF8(font, _text.c_str(), &width, nullptr);
    while (width > targetWidth) {
        height = height * targetWidth / width;
        font = resources::font(res::FontId::Mecha, height);
        TTF_SizeUTF8(font, _text.c_str(), &width, nullptr);
    }
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        font,
        _text.c_str(),
        SDL_Color{0, 0, 0, 255},
        SDL_Color{_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a});
    if (surface) {
        _textureSize.x = surface->w;
        _textureSize.y = surface->h;

        _texture = SDL_CreateTextureFromSurface(media::renderer(), surface);
        SDL_FreeSurface(surface);
    }
}
