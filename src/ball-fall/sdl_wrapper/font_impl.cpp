#include "font_impl.hpp"
#include "surface_impl.hpp"

#include <cassert>
#include <utility>

namespace sdl {
namespace ttf {

FontImpl::FontImpl(std::shared_ptr<Library> ttfLibrary, TTF_Font* font)
    : _ttfLibrary(std::move(ttfLibrary))
    , _font(font, TTF_CloseFont)
{
    assert(_ttfLibrary);
    assert(_font);
}

std::shared_ptr<Surface> FontImpl::renderUtf8Solid(
    const std::string& text, const SDL_Color& fg) const
{
    return std::make_shared<SurfaceImpl>(
        _ttfLibrary->sdlLibrary(), TTF_RenderUTF8_Solid(text.c_str(), fg));
}

std::shared_ptr<Surface> FontImpl::renderUtf8Shaded(
    const std::string& text,
    const SDL_Color& fg,
    const SDL_Color& bg) const
{
    return std::make_shared<SurfaceImpl>(
        _ttfLibrary->sdlLibrary(), TTF_RenderUTF8_Shaded(text.c_str(), fg, bg));
}

std::shared_ptr<Surface> FontImpl::renderUtf8Blended(
    const std::string& text, const SDL_Color& fg) const
{
    return std::make_shared<SurfaceImpl>(
        _ttfLibrary->sdlLibrary(), TTF_RenderUTF8_Blended(text.c_str(), fg));
}

}} // namespace sdl::ttf
