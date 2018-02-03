#include "sdl_library_impl.hpp"

namespace sdl {

LibraryImpl::LibraryImpl()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        throw std::runtime_error("SDL_Init failed");
    }

}

LibraryImpl::~LibraryImpl()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//
// Events
//

std::optional<SDL_Event> LibraryImpl::pollEvent() const
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        return event;
    } else {
        return {};
    }
}

//
// Display and window management
//

std::shared_ptr<Window> LibraryImpl::createWindow(
    const std::string& title,
    int x,
    int y,
    int w,
    int h,
    Uint32 flags) const
{
    SDL_Window* window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    return std::make_shared<WindowImpl>(window);
}

} // namespace sdl
