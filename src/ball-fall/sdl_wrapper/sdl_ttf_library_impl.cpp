#include "sdl_ttf_library_impl.hpp"

#include <SDL2/SDL_ttf.h>

#include <cassert>
#include <utility>

namespace sdl {
namespace ttf {

LibraryImpl::LibraryImpl(std::shared_ptr<sdl::Library> sdlLibrary)
    : _sdlLibrary(std::move(sdlLibrary))
{
    assert(_sdlLibrary);

    if (TTF_Init() == -1) {
        throw std::runtime_error("TTF_Init failed");
    }
}

LibraryImpl::~LibraryImpl()
{
    TTF_Quit();
}

const std::shared_ptr<sdl::Library> LibraryImpl::sdlLibrary() const
{
    return _sdlLibrary;
}

std::shared_ptr<Font> LibraryImpl::openFont(
    const std::string& file, int ptSize) const
{
    return std::make_shared<FontImpl>(
        shared_from_this(), TTF_OpenFont(file.c_str(), ptSize));
}

}} // namespace sdl::ttf