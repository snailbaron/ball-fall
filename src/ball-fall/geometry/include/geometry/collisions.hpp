#pragma once

#include <geometry/geometry.hpp>

#include <optional>

namespace geometry {

struct Collision {
    Vector objectCenter;
    Vector collisionPoint;
    double timeToCollision;
};

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Line& line);

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Vector& point);

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Segment& segment);

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const AxisRect& rect);

} // namespace geometry
