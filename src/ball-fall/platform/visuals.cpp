#include <platform/visuals.hpp>

#include <SDL2/SDL.h>

Texture::Texture()
    : width(0)
    , height(0)
    , ptr(nullptr)
{ }

Texture::Texture(int width, int height, SDL_Texture* texture)
    : width(width)
    , height(height)
    , ptr(texture)
{ }

Texture::~Texture()
{
    if (ptr) {
        SDL_DestroyTexture(ptr);
    }
}
