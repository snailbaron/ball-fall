#include "window_impl.hpp"

#include <sdl_wrapper.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdexcept>

namespace sdl {

class LibraryImpl : public Library {
public:
    LibraryImpl()
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1) {
            throw std::runtime_error("SDL_Init failed");
        }

        if (TTF_Init() == -1) {
            throw std::runtime_error("TTF_Init failed");
        }

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1) {
            throw std::runtime_error("IMG_Init failed");
        }
    }

    ~LibraryImpl()
    {
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    //
    // Events
    //

    std::optional<SDL_Event> pollEvent() const
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

    std::shared_ptr<Window> createWindow(
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
};

namespace {

std::shared_ptr<Sdl> g_sdl;

} // namespace

void init()
{
    if (!g_sdl) {
        g_sdl = std::make_shared<sdl::LibraryImpl>();
    }
}

void quit()
{
    g_sdl.reset();
}

} // namespace sdl

std::shared_ptr<sdl::Library> sdl()
{
    initSdl();
    return g_sdl;
}