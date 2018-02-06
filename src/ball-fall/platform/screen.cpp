#include <platform/screen.hpp>

#include <utility>

Screen::Screen(sdl::Renderer renderer)
    : _renderer(std::move(renderer))
{ }

void Screen::clear(const Color& color)
{
    _renderer.setDrawColor(color.r, color.g, color.b, color.a);
    _renderer.clear();
}

void Screen::present()
{
    _renderer.present();
}

void Screen::drawRect(
    const Vector<int>& position, const Vector<int>& size, const Color& color)
{
    _renderer.setDrawColor(color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, size.x, size.y};
    _renderer.fillRect(rect);
}

void Screen::drawRoundedBox(
    const Vector<int16_t>& position,
    const Vector<int16_t>& size,
    int16_t cornerRadius,
    const Color& color)
{
    renderer.roundedBoxRGBA(
        position.x, position.y, position.x + size.x, position.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
}

void Screen::drawSprite(const Vector<int>& position, const Sprite& sprite)
{
    SDL_Rect dstRect {
        position.x,
        position.y,
        position.x + texture.width,
        position.y + texture.height
    };
    _renderer.copy(sprite.texture, nullptr, dstRect);
}
