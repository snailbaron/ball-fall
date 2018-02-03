#pragma once

#include <platform/events.hpp>
#include <platform/types.hpp>

#include <resource_ids.hpp>

#include <memory>

namespace platform {

void init();
void kill();

} // namespace platform

namespace resource {

std::shared_ptr<Font> font(res::FontId fontId, int ptSize);

std::shared_ptr<Texture> texture(res::BitmapId bitmapId);

std::shared_ptr<Texture> textTexture(
    const std::string& text,
    res::FontId font,
    const Color& textColor,
    const Color& bgColor,
    const Vector<int>& desiredSize);

} // namespace resource

namespace screen {

void show();

void clear(const Color& color);
void present();

void drawRect(
    const Vector<int>& position,
    const Vector<int>& size,
    const Color& color);

void drawRoundedBox(
    const Vector<int16_t>& position,
    const Vector<int16_t>& size,
    int16_t cornerRadius,
    const Color& color);

void drawTexture(
    const Vector<int>& position,
    const std::shared_ptr<Texture>& texture);

} // namespace screen
