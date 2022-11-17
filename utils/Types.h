#pragma once

#include <concepts>

namespace gk
{

template<typename T>
struct Color3
{
    T r;
    T g;
    T b;

    auto toBytes() const -> const T*
    {
        return &r;
    }
};

template<typename T>
struct Vector2
{
    T x;
    T y;

    auto toBytes() const -> const T*
    {
        return &x;
    }
};

template<typename T>
struct Vector3
{
    T x;
    T y;
    T z;
    auto toBytes() const -> const T*
    {
        return &x;
    }
};

using Color3f = Color3<float>;
using Color3ub = Color3<uint8_t>;

using Vector2f = Vector2<float>;
using Vector2u = Vector2<uint32_t>;
using Vector2i = Vector2<int>;

using Vector3f = Vector3<float>;
using Vector3u = Vector3<uint32_t>;
using Vector3i = Vector3<int>;

}

