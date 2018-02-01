#pragma once

#include <utility>
#include <type_traits>

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

template <class Target, class Source>
Vector<Target> vectorCast(const Vector<Source>& source)
{
    return {static_cast<Target>(source.x), static_cast<Target>(source.y)};
}

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

template <class L, class R>
Vector<decltype(std::declval<L>() + std::declval<R>())>
operator+(const Vector<L>& left, const Vector<R>& right)
{
    return {left.x + right.x, left.y + right.y};
}

template <class L, class R>
Vector<decltype(std::declval<L>() - std::declval<R>())>
operator-(const Vector<L>& left, const Vector<R>& right)
{
    return {left.x - right.x, left.y - right.y};
}
