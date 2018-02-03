#include "lru_cache.hpp"

#include <resources_generated.h>
#include <platform.hpp>

#include <memory>
#include <vector>

class Resources {
public:
    Resources();

    void load();
    void clear();

    std::shared_ptr<Font> font(res::FontId fontId, int ptSize);
    std::shared_ptr<Texture> texture(res::BitmapId bitmapId);

private:
    std::shared_ptr<Font> loadFont(res::FontId fontId, int ptSize) const;

    std::vector<std::vector<uint8_t>> _fonts;
    MultiKeyLruCache<std::shared_ptr<Font>, res::FontId, int> _sizedFonts;
    std::vector<std::shared_ptr<Texture>> _textures;
};
