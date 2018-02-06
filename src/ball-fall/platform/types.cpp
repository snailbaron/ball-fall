#include <platform/types.hpp>

#include <utility>

Sprite::Sprite(sdl::Texture texture)
    : _texture(std::move(texture))
{ }

const sdl::Texture& Sprite::texture() const
{
    return _texture;
}

const SDL_Rect* Sprite::srcrect() const
{
    return nullptr;
}
