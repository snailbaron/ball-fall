#include "scene.hpp"
#include <platform.hpp>

#include "resource_ids.hpp"

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
    SDL_Rect dstRect {
        static_cast<int>(_ballPosition.x * 10),
        static_cast<int>(_ballPosition.y * 10),
        32,
        32
    };
    SDL_RenderCopy(media::renderer(), resources::texture(res::BitmapId::Ball), nullptr, &dstRect);


}