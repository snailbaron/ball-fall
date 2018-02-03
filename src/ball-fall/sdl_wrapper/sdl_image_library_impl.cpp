#include "sdl_image_library_impl.hpp"
#include "surface_impl.hpp"

#include <SDL2/SDL_image.h>

#include <cassert>
#include <stdexcept>
#include <utility>

namespace sdl {
namespace img {

LibraryImpl::LibraryImpl(std::shared_ptr<sdl::Library> sdlLibrary)
    : _sdlLibrary(std::move(sdlLibrary))
{
    assert(_sdlLibrary);

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1) {
        throw std::runtime_error("IMG_Init failed");
    }
}

LibraryImpl::~LibraryImpl()
{
    IMG_Quit();
}

std::shared_ptr<Surface> LibraryImpl::load(const std::string& file) const
{
    return std::make_shared<SurfaceImpl>(
        shared_from_this(), IMG_Load(file.c_str()));
}

}} // namespace sdl::img