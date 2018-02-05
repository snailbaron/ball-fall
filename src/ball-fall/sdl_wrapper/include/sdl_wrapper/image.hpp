#pragma once

#include "surface.hpp"

#include <SDL2/SDL_image.h>

#include <string>

namespace sdl {
namespace img {

void init(int flags)
{
    IMG_Init(flags);
}

void quit()
{
    IMG_Quit();
}

Surface LibraryImpl::load(const std::string& file)
{
    return Surface(IMG_Load(file.c_str()));
}

}} // namespace sdl::img