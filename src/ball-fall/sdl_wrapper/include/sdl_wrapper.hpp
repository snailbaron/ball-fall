#pragma once

#include <sdl_wrapper/sdl_library.hpp>
#include <sdl_wrapper/sdl_image_library.hpp>
#include <sdl_wrapper/sdl_ttf_library.hpp>

namespace sdl {

void init();
void quit();

std::shared_ptr<Library> library();

namespace img {

void init();
void quit();

std::shared_ptr<Library> library();

} // namespace img

namespace ttf {

void init();
void quit();

std::shared_ptr<Library> library();

} // namespace ttf

} // namespace sdl
