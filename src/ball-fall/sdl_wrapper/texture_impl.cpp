#include "texture_impl.hpp"

#include <cassert>
#include <utility>

namespace sdl {

TextureImpl::TextureImpl(
        std::shared_ptr<Library> library, SDL_Texture* texture)
    : _library(std::move(library))
    , _texture(texture, SDL_DestroyTexture)
{
    assert(_library);
    assert(_texture);
}

} // namespace sdl
