#include <platform/screen.hpp>

Screen::Config::Config()
    : title("Ball Fall")
    , width(1024)
    , height(768)
{ }

Screen::Screen(const Config& config);
{
    _window = sdl::createWindow(
        config.title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.width,
        config.height,
        0);
    _renderer = _window.createRenderer(
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Screen::~Screen()
{
    _renderer.reset();
    _window.reset();
}

void Screen::show()
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
