#pragma once

#include <algorithm>

namespace geometry {

/**
 * Vector in 2D space.
 *
 * Vectors support basic arithmetic operations.
 *
 * Right-handed orientation is assumed for operations that depend on it. That
 * is:
 * * Y axis unit vector is X axis unit vector turned 90 degrees CCW
 * * X, Y, Z base is right-handed (which is important for cross product)
 */
struct Vector {
    Vector();
    Vector(double x, double y);
    Vector(const Vector& other);

    Vector operator-() const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);

    static const Vector zero;

    double x;
    double y;
};

Vector operator+(Vector lhs, const Vector& rhs);
Vector operator-(Vector lhs, const Vector& rhs);
Vector operator*(Vector lhs, double scalar);
Vector operator*(double scalar, Vector rhs);
Vector operator/(Vector lhs, double scalar);

double length(const Vector& v);

/** Vector turned 90 degrees CCW */
Vector ccw90(const Vector& v);

/** Vector turned 90 degrees CW */
Vector cw90(const Vector& v);

/** Dot product of two vectors */
double dot(const Vector& v1, const Vector& v2);

/** Z coordinate of cross product of two vectors */
double cross(const Vector& v1, const Vector& v2);

/** Normalized vector */
Vector normalized(const Vector& v);

/** Projection of vector v onto line base */
Vector projection(const Vector& v, const Vector& direction);

/** Ort of vector v projected onto direction */
Vector ort(const Vector& v, const Vector& direction);

Vector mirrorBy(const Vector& v, const Vector& mirror);
Vector mirrorAlong(const Vector& v, const Vector& direction);

} // namespace geometry
