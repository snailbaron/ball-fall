#include "screen_impl.hpp"
#include "resources_impl.hpp"

#include <platform.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdexcept>
#include <memory>

namespace platform {

namespace {

std::unique_ptr<Screen> g_screen;
std::unique_ptr<Resources> g_resources;

} // namespace

void init()
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

    g_resources = std::make_unique<ResourcesImpl>();
    g_resources->load();
    g_screen = std::make_unique<ScreenImpl>();
}

void kill()
{
    g_screen.reset();
    g_resources->clear();
    g_resources.reset();

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

} // namespace platform
