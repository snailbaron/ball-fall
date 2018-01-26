#include "scene.hpp"
#include "../media.hpp"

void PlatformSprite::render() const
{
}

Scene::Scene()
{
    subscribe<evt::PlatformMove>(evt::bus(), [this] (const auto& event) {
        _platformPosition = static_cast<float>(event.position);
    });
}

void Scene::render() const
{
    for (const auto& coordSpritePair : _bricks) {
        const auto& coords = coordSpritePair.first;
        const auto& sprite = coordSpritePair.second;

        SDL_Rect dstRect {
            coords.x * 10,
            coords.y * 10,
            16,
            10};
        SDL_RenderCopy(
            media::renderer(),
            resources::texture(sprite.bitmapId),
            nullptr,
            &dstRect);
    }

    SDL_Rect dstRect {
        static_cast<int>(_ballPosition.x * 10),
        static_cast<int>(_ballPosition.y * 10),
        32,
        32
    };
    SDL_RenderCopy(media::renderer(), resources::texture(res::BitmapId::Ball), nullptr, &dstRect);
}