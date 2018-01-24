#include "geometry.hpp"

#include <cmath>

namespace geometry {

//
// Line
//

Line::Line(Vector norm, double baseValue)
    : _norm(norm)
    , _baseValue(baseValue)
{ }

Line::Line(Vector basePoint, Vector direction)
    : _norm(normalized(ccw90(direction)))
    , _baseValue(dot(basePoint, _norm))
{ }

Line Line::directed(const Vector& basePoint, const Vector& direction)
{
    return Line(basePoint, direction);
}

Line Line::betweenPoints(const Vector& p1, const Vector& p2)
{
    return Line(p1, p2 - p1);
}

const Vector& Line::norm() const
{
    return _norm;
}

double Line::signedDistanceTo(const Vector& point) const
{
    return dot(point, _norm) - _baseValue;
}

double Line::distanceTo(const Vector& point) const
{
    return std::abs(signedDistanceTo(point));
}

Line Line::moved(double offset) const
{
    return Line(_norm, _baseValue + offset);
}

//
// Circle
//

Circle::Circle(Vector center, double radius)
    : center(std::move(center))
    , radius(std::move(radius))
{ }

Circle::Circle(double x, double y, double radius)
    : center(x, y)
    , radius(radius)
{ }

Circle& Circle::operator+=(const Vector& vector)
{
    center += vector;
    return *this;
}

//
// Segment

Segment::Segment(Vector start, Vector end)
    : start(std::move(start))
    , end(std::move(end))
{ }

Segment::Segment(double x1, double y1, double x2, double y2)
    : start(x1, y1)
    , end(x2, y2)
{ }

Segment& Segment::operator+=(const Vector& vector)
{
    start += vector;
    end += vector;
    return *this;
}

//
// AxisRect
//

AxisRect::AxisRect(double x, double y, double w, double h)
    : position(x, y)
    , size(w, h)
{ }

AxisRect::AxisRect(Vector p0, Vector p1)
    : position(p0)
    , size(p1 - p0)
{ }

std::vector<Segment> AxisRect::segments() const
{
    return {
        { position.x, position.y, position.x + size.x, position.y },
        { position.x + size.x, position.y, position.x + size.x, position.y + size.y },
        { position.x + size.x, position.y + size.y, position.x, position.y + size.y },
        { position.x, position.y + size.y, position.x, position.y },
    };
}

AxisRect& AxisRect::operator+=(const Vector& vector)
{
    position += vector;
    return *this;
}

//
// Various functions on geometry primitives
//

AxisRect operator+(AxisRect rect, const Vector& vector)
{
    rect += vector;
    return rect;
}

AxisRect operator+(const Vector& vector, AxisRect rect)
{
    return rect + vector;
}

double distance(const Vector& v1, const Vector& v2)
{
    return length(v1 - v2);
}

double distance(const Vector& p, const Line& l)
{
    return l.distanceTo(p);
}

double distance(const Line& l, const Vector& p)
{
    return distance(p, l);
}

bool between(const Vector& p, const Vector& p1, const Vector& p2)
{
    return dot(p1 - p, p2 - p) < 0;
}

std::optional<Vector> lineCross(const Line& l1, const Line& l2)
{
    double d = l1.norm().x * l2.norm().y - l1.norm().y * l2.norm().x;
    if (d == 0.0) {
        return {};
    }

    double d1 = l1.baseValue() * l2.norm().y - l2.baseValue() * l1.norm().y;
    double d2 = l1.norm().x * l2.baseValue() - l2.norm().x * l1.baseValue();
    return Vector(d1 / d, d2 / d);
}

Vector projection(const Vector& p, const Line& l)
{
    return p - projection(p, l.norm());
}

} // namespace geometry
