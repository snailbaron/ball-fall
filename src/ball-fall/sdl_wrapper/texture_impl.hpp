#pragma once

#include "sdl_library_impl.hpp"

#include <sdl_wrapper/texture.hpp>

#include <memory>

namespace sdl {

class TextureImpl : public Texture {
public:
    TextureImpl(std::shared_ptr<Library> library, SDL_Texture* texture);

private:
    std::shared_ptr<LibraryImpl> _library;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
};

} // namespace sdl
