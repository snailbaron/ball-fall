#pragma once

#include <resource_ids.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace res {

void load(const std::string& resourceFile, SDL_Renderer* renderer);

TTF_Font* font(res::FontId fontId, int ptSize);
const SDL_Texture* texture(res::BitmapId bitmapId);

} // namespace res
