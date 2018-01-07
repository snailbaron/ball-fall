#pragma once

#include <utility>

template <class T>
struct Vector {
    Vector()
        : x{}, y{}
    { }

    Vector(T x, T y)
        : x(std::move(x)), y(std::move(y))
    { }

    T x;
    T y;
};

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right)
{
    return left.x == right.x && left.y == right.y;
}

template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right)
{
    return !(left == right);
}