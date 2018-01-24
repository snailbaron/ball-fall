#include "field.hpp"
#include "geometry/collisions.hpp"
#include "events.hpp"

#include <limits>

const geometry::Vector Field::Size {100, 100};

Field::Field()
{
    auto brickShape = geometry::AxisRect(-5, -5, 10, 10);

    _bricks.emplace_back();
    _bricks.back().look = Brick::Look::Yellow;
    _bricks.back().position = {0, 20};
    _bricks.back().shape = brickShape;

    _bricks.emplace_back();
    _bricks.back().look = Brick::Look::Red;
    _bricks.back().position = {10, 50};
    _bricks.back().shape = brickShape;

    _ball.velocity = {10, 10};
}

void Field::update(double delta)
{
    if (length(_ball.velocity) > 0) {
        auto timeLeft = delta;
        auto collision = closestBallCollision();
        while (collision.timeToCollision <= timeLeft) {
            timeLeft -= collision.timeToCollision;

            _ball.shape.center = collision.objectCenter;
            _ball.velocity = mirrorBy(
                _ball.velocity,
                collision.objectCenter - collision.collisionPoint);

            collision = closestBallCollision();
        }

        _ball.shape.center += _ball.velocity * timeLeft;

        evt::bus().send(evt::BallMove{_ball.shape.center});
    }
}

geometry::Collision Field::closestBallCollision() const
{
    auto betterThan = [] (
        const std::optional<geometry::Collision>& left,
        const std::optional<geometry::Collision>& right)
    {
        return left &&
            (!right || left->timeToCollision < right->timeToCollision);
    };

    auto bestCollision = std::optional<geometry::Collision>();
    for (const auto& brick : _bricks) {
        auto brickGeometry = brick.position + brick.shape;
        auto collision =
            geometry::collision(_ball.shape, _ball.velocity, brickGeometry);
        if (betterThan(collision, bestCollision)) {
            bestCollision = collision;
        }
    }

    if (bestCollision) {
        return *bestCollision;
    }

    auto screenFrame = geometry::AxisRect(-Size / 2, Size / 2);
    auto screenCollision =
        geometry::collision(_ball.shape, _ball.velocity, screenFrame);
    return *screenCollision;
}