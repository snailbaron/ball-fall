#include <geometry/2dspace.hpp>

namespace geometry {

//
// Vector
//

const Vector Vector::zero(0, 0);

Vector::Vector()
    : x()
    , y()
{ }

Vector::Vector(double x, double y)
    : x(x)
    , y(y)
{ }

Vector::Vector(const Vector& other)
    : x(other.x)
    , y(other.y)
{ }

Vector Vector::operator-() const
{
    return Vector(-x, -y);
};

Vector& Vector::operator+=(const Vector& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector& Vector::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector operator+(Vector lhs, const Vector& rhs)
{
    lhs += rhs;
    return lhs;
}

Vector operator-(Vector lhs, const Vector& rhs)
{
    lhs -= rhs;
    return lhs;
}

Vector operator*(Vector lhs, double scalar)
{
    lhs *= scalar;
    return lhs;
}

Vector operator*(double scalar, Vector rhs)
{
    rhs *= scalar;
    return rhs;
}

Vector operator/(Vector lhs, double scalar)
{
    lhs /= scalar;
    return lhs;
}

double length(const Vector& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vector ccw90(const Vector& v)
{
    return Vector(-v.y, v.x);
}

Vector cw90(const Vector& v)
{
    return Vector(v.y, -v.x);
}

double dot(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double cross(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

Vector normalized(const Vector& v)
{
    return v / length(v);
}

Vector projection(
    const Vector& v,
    const Vector& direction)
{
    Vector axis = normalized(direction);
    double coord = dot(v, axis);
    return axis * coord;
}

Vector ort(const Vector& v, const Vector& direction)
{
    return v - projection(v, direction);
}

Vector mirrorBy(const Vector& v, const Vector& mirror)
{
    return v - 2 * ort(v, mirror);
}

Vector mirrorAlong(
    const Vector& v,
    const Vector& direction)
{
    return v - double(2) * projection(v, direction);
}

} // namespace geometry
