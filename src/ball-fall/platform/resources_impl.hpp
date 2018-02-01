#include "lru_cache.hpp"
#include <platform/resources.hpp>

#include <resources_generated.h>

#include <memory>
#include <vector>

class ResourcesImpl : public Resources {
public:
    ResourcesImpl();

    void load() override;
    void clear() override;

    TTF_Font* font(res::FontId fontId, int ptSize) override;
    const Texture& texture(res::BitmapId bitmapId) override;

private:
    using FontPtr = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;
    FontPtr loadFont(res::FontId fontId, int ptSize);

    std::vector<std::vector<uint8_t>> _fonts;
    MultiKeyLruCache<FontPtr, res::FontId, int> _sizedFonts;
    std::vector<Texture> _textures;
};
