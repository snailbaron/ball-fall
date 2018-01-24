#include "scene.hpp"

Scene::Scene(SDL_Renderer* renderer, Resources& resources)
    : _renderer(renderer)
    , _resources(resources)
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
        SDL_RenderCopy(_renderer, _resources.texture(sprite.bitmapId), nullptr, &dstRect);
    }

    SDL_Rect dstRect {
        _ballPosition.x * 10,
        _ballPosition.y * 10,
        32,
        32
    };
    SDL_RenderCopy(_renderer, _resources.texture(res::BitmapId::Ball), nullptr, &dstRect);
}