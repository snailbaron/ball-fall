#pragma once

#include <platform/resources.hpp>
#include <platform/screen.hpp>

#include <util.hpp>

#include <utility>
#include <tuple>

namespace flat = BallFall::Resources;

Resources::Resources(sdl::Renderer renderer)
    : _renderer(std::move(renderer))
    , _sizedFonts(
        20,
        [this] (res::FontId fontId, int ptSize) {
            return loadFont(fontId, ptSize);
        })
{ }

void Resources::load(const std::string& resourceFile)
{
    auto resourceData = util::readFile(resourceFile);
    const auto* resources = flat::GetResources(resourceData.data());

    for (const auto& font : *resources->fonts()) {
        _fonts.emplace_back(
            font->data()->data(),
            font->data()->data() + font->data()->size());
    }

    for (const auto& bitmap : *resources->bitmaps()) {
        auto surface = sdl::img::loadRW(
            SDL_RWFromConstMem(
                bitmap->data()->data(), bitmap->data()->size()), 0);

        int width = surface.w;
        int height = surface.h;

        auto texture = _renderer.createTextureFromSurface(surface);
        _textures.push_back(std::make_shared<Sprite>(std::move(texture)));
    }
}

void Resources::clear()
{
    _sizedFonts.clear();
    _fonts.clear();
    _textures.clear();
}

sdl::ttf::Font Resources::font(res::FontId fontId, int ptSize)
{
    return _sizedFonts.get(fontId, ptSize);
}

std::shared_ptr<Image> Resources::image(res::BitmapId bitmapId)
{
    return _images.at(static_cast<size_t>(bitmapId));
}

std::shared_ptr<Image> Resources::textImage(
    const std::string& text,
    res::FontId fontId,
    const Color& textColor,
    const Color& bgColor,
    const util::Vector<int>& desiredSize)
{
    int height = desiredSize.y;
    auto font = this->font(fontId, height);

    int width;
    std::tie(width, std::ignore) = font.sizeUtf8(text);
    while (width > desiredSize.x) {
        height = height * desiredSize.x / width;
        font = this->font(fontId, height);
        std::tie(width, std::ignore) = font.sizeUtf8(text);
    }

    auto surface =
        font.renderUtf8Shaded(text, sdlColor(textColor), sdlColor(bgColor));
    auto texture = _renderer.createTextureFromSurface(surface);
    return std::make_shared<Sprite>(texture);
}

sdl::ttf::Font Resources::loadFont(res::FontId fontId, int ptSize) const
{
    auto index = static_cast<size_t>(fontId);
    const auto& fontData = _fonts.at(index);
    return sdl::ttf::openFont(
        SDL_RWFromConstMem(fontData.data(), (int)fontData.size()),
        0,
        ptSize);
}