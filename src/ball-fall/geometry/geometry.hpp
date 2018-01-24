#pragma once

/**
 * Geometry primitives
 */

#include "2dspace.hpp"

#include <vector>
#include <utility>
#include <optional>

namespace geometry {

/**
 * Infinite line
 */
class Line {
public:
    static Line directed(const Vector& basePoint, const Vector& direction);
    static Line betweenPoints(const Vector& p1, const Vector& p2);

    const Vector& norm() const;
    double baseValue() const { return _baseValue; }

    double signedDistanceTo(const Vector& point) const;
    double distanceTo(const Vector& point) const;
    Line moved(double offset) const;

private:
    Line(Vector norm, double baseValue);
    Line(Vector basePoint, Vector direction);

    Vector _norm;
    double _baseValue;
};

/**
 * Circle.
 */
struct Circle {
    Circle() {}
    Circle(Vector center, double radius);
    Circle(double x, double y, double radius);

    Circle& operator+=(const Vector& vector);

    Vector center;
    double radius = 0;
};

/**
 * Segment connecting two points in space.
 */
struct Segment {
    Segment(Vector start, Vector end);
    Segment(double x1, double y1, double x2, double y2);

    Segment& operator+=(const Vector& vector);

    Vector start;
    Vector end;
};

/**
 * Rectangle with segments parallel to axes.
 */
struct AxisRect {
    AxisRect() {}
    AxisRect(double x, double y, double w, double h);
    AxisRect(Vector p0, Vector p1);

    std::vector<Segment> segments() const;

    AxisRect& operator+=(const Vector& vector);

    Vector position;
    Vector size;
};

// Various functions on geometry primitives

AxisRect operator+(AxisRect rect, const Vector& vector);
AxisRect operator+(const Vector& vector, AxisRect rect);

double distance(const Vector& v1, const Vector& v2);
double distance(const Vector& p, const Line& l);
double distance(const Line& l, const Vector& p);

Vector projection(const Vector& p, const Line& l);

bool between(const Vector& p, const Vector& p1, const Vector& p2);

std::optional<Vector> lineCross(const Line& l1, const Line& l2);

} // namespace geometry
