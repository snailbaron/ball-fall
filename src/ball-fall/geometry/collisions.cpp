#include <geometry/collisions.hpp>

#include <algorithm>

namespace geometry {

namespace {

template <class FirstObject, class... OtherObjects>
std::optional<Collision> anyCollision(
    const Circle& circle,
    const Vector& velocity,
    const FirstObject& firstObject,
    const OtherObjects&... otherObjects)
{
    auto firstCollision = collision(circle, velocity, firstObject);
    if (firstCollision) {
        return firstCollision;
    }
    return anyCollision(circle, velocity, otherObjects...);
}

std::optional<Collision> anyCollision(const Circle&, const Vector&)
{
    return {};
}

} // namespace

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Line& line)
{
    auto orthoSpeed = dot(velocity, line.norm());
    auto movingTowardsLine =
        line.signedDistanceTo(circle.center) * orthoSpeed < 0;
    if (!movingTowardsLine) {
        return {};
    }

    auto trajectory = Line::directed(circle.center, velocity);
    auto touchLine = line.moved(circle.radius * (orthoSpeed < 0));
    auto targetPoint = lineCross(trajectory, touchLine);
    if (!targetPoint) {
        return {};
    }
    auto distanceToCollision = distance(circle.center, *targetPoint);
    auto timeToCollision = distanceToCollision / length(velocity);

    Collision collision;
    collision.objectCenter = *targetPoint;
    collision.collisionPoint = *targetPoint - line.norm() * circle.radius;
    collision.timeToCollision = timeToCollision;

    return collision;
}

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Vector& point)
{
    auto trajectory = Line::directed(circle.center, velocity);
    auto vectorToTarget = point - circle.center;
    auto movingTowardsPoint = dot(velocity, vectorToTarget) > 0;
    if (!movingTowardsPoint) {
        return {};
    }

    auto distanceFromTrajectory = distance(trajectory, point);
    if (distanceFromTrajectory > circle.radius) {
        return {};
    }

    auto proj = projection(point, trajectory);
    auto offset = std::sqrt(circle.radius * circle.radius -
        distanceFromTrajectory * distanceFromTrajectory);
    auto newCenter = proj - normalized(velocity) * offset;
    auto distanceToCollision = distance(circle.center, newCenter);
    auto timeToCollision = distanceToCollision / length(velocity);

    Collision collision;
    collision.objectCenter = newCenter;
    collision.collisionPoint = point;
    collision.timeToCollision = timeToCollision;

    return collision;
}

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const Segment& segment)
{
    auto lineCollision = collision(
        circle, velocity, Line::betweenPoints(segment.start, segment.end));
    if (lineCollision && between(
            lineCollision->collisionPoint, segment.start, segment.end)) {
        return lineCollision;
    }

    return anyCollision(circle, velocity, segment.start, segment.end);
}

std::optional<Collision> collision(
    const Circle& circle,
    const Vector& velocity,
    const AxisRect& rect)
{
    auto closestCollision = std::optional<Collision>();
    auto closestTime = std::numeric_limits<double>::infinity();

    for (const auto& segment : rect.segments()) {
        auto col = collision(circle, velocity, segment);
        if (col && col->timeToCollision < closestTime) {
            closestCollision = col;
            closestTime = col->timeToCollision;
        }
    }

    return closestCollision;
}

} // namespace geometry
