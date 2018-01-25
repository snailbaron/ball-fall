#pragma once

#include "resources.hpp"
#include "../vector.hpp"
#include "../events.hpp"

#include <SDL2/SDL.h>

#include <map>

struct BrickSprite {
    res::BitmapId bitmapId;
    int x;
    int y;
};

class Scene : public evening::Subscriber {
public:
    Scene();

    void render() const;

private:
    std::map<Vector<int>, BrickSprite> _bricks;
    geometry::Vector _ballPosition;
    float _platformPosition;
};
