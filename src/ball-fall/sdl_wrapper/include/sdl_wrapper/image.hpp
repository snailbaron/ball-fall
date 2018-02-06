#pragma once

#include <sdl_wrapper/surface.hpp>

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

Surface load(const std::string& file)
{
    return Surface(IMG_Load(file.c_str()));
}

Surface loadRW(SDL_RWops* src, int freesrc)
{
    return Surface(IMG_Load_RW(src, freesrc));
}

}} // namespace sdl::img