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
}