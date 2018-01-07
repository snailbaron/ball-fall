#pragma once

#include "lru_cache.hpp"

#include <resource_ids.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

class Resources {
public:
    Resources();

    void load(SDL_Renderer* renderer);

    TTF_Font* font(res::FontId fontId, int ptSize);
    const SDL_Texture* texture(res::BitmapId bitmapId);

private:
    using TexturePtr = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;
    using FontPtr = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;

    FontPtr loadFont(res::FontId fontId, int ptSize);

    std::vector<std::vector<uint8_t>> _fonts;
    MultiKeyLruCache<FontPtr, res::FontId, int> _sizedFonts;
    std::vector<TexturePtr> _textures;
};
