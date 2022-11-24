#pragma once

#include <concepts>
#include <cstdint>
#include <cmath>
#include <iostream>

#define VAR(x) #x

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

using Vector2d = Vector2<double>;
using Vector2f = Vector2<float>;
using Vector2u = Vector2<uint32_t>;
using Vector2i = Vector2<int>;

using Vector3d = Vector3<double>;
using Vector3f = Vector3<float>;
using Vector3u = Vector3<uint32_t>;
using Vector3i = Vector3<int>;

namespace vec
{

template<typename T>
constexpr auto subtract(Vector3<T> v1, Vector3<T> v2) noexcept -> Vector3<T>
{
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

template<typename T>
constexpr auto add(Vector3<T> v1, Vector3<T> v2) noexcept -> Vector3<T>
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

template<typename T>
constexpr auto multiply(Vector3<T> v1, T value) noexcept -> Vector3<T>
{
    return {v1.x * value, v1.y * value, v1.z * value};
}

template<typename T>
constexpr auto divide(Vector3<T> v1, T value) noexcept -> Vector3<T>
{
    return {v1.x / value, v1.y / value, v1.z / value};
}

template<typename T>
constexpr auto distance(Vector3<T> v1, Vector3<T> v2) noexcept -> T
{
    const auto x = v1.x - v2.x;
    const auto y = v1.y - v2.y;
    const auto z = v1.z - v2.z;

    return static_cast<T>(std::sqrt(x * x + y * y + z * z));
}

template<typename T>
constexpr auto length(Vector3<T> v1) noexcept -> T
{
    return static_cast<T>(std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}

template<typename T>
constexpr auto normalized(Vector3<T> v1) noexcept -> Vector3<T>
{
    const auto mag = length(v1);
    if (mag == static_cast<T>(0))
    {
        return v1;
    }
    return divide(v1, mag);
}

template<typename T>
constexpr auto cross(Vector3<T> v1, Vector3<T> v2) -> Vector3<T>
{
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}


template<typename T>
auto print(std::string_view name, Vector3<T> v1) -> void
{
    std::cout << name << ": " << "x: " << v1.x << "; y: " << v1.y << "; z: " << v1.z << "\n";
}

template<typename T>
auto print(Vector3<T> v1) -> void
{
    print("vec", v1);
}


}

}

