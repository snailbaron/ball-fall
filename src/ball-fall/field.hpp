#pragma once

#include "geometry/collisions.hpp"

#include <vector>

struct Brick {
public:
    enum class Look {
        Yellow,
        Red,
        Green,
    };

    enum class Prize {
        None,
        Grow,
        Shrink,
    };

    Look look;
    Prize prize;
    geometry::Vector position;
    geometry::AxisRect shape;
};

struct Platform {
    geometry::Vector position;
    geometry::AxisRect shape;
};

struct Ball {
    geometry::Circle shape;
    geometry::Vector velocity;
};

class Field {
public:
    Field();

    void update(double delta);

private:
    static const geometry::Vector Size;

    static constexpr size_t GridWidth = 10;
    static constexpr size_t GridHeight = 10;

    geometry::Collision closestBallCollision() const;

    std::vector<Brick> _bricks;
    Platform _platform;
    Ball _ball;
};