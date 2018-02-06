#include <platform/internal/lru_cache.hpp>
#include <platform/types.hpp>

#include <resources_generated.h>

#include <sdl_wrapper.hpp>

#include <memory>
#include <vector>

class Resources {
public:
    Resources(sdl::Renderer renderer);

    void load(const std::string& resourceFile);
    void clear();

    sdl::ttf::Font font(res::FontId fontId, int ptSize);
    std::shared_ptr<Image> image(res::BitmapId bitmapId);

    std::shared_ptr<Image> textImage(
        const std::string& text,
        res::FontId fontId,
        const Color& textColor,
        const Color& bgColor,
        const util::Vector<int>& desiredSize);

private:
    sdl::ttf::Font loadFont(res::FontId fontId, int ptSize) const;

    sdl::Renderer _renderer;
    std::vector<std::vector<uint8_t>> _fonts;
    internal::MultiKeyLruCache<sdl::ttf::Font, res::FontId, int> _sizedFonts;
    std::vector<std::shared_ptr<Image>> _images;
};
