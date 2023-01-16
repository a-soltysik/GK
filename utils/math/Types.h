#pragma once

#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GLFW/glfw3.h>

#include <concepts>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>

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

    [[nodiscard]]
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

    [[nodiscard]]
    auto toBytes() const -> const T*
    {
        return &x;
    }
};

template<typename T>
struct Vector4
{
    T x;
    T y;
    T z;
    T w;

    [[nodiscard]]
    auto toBytes() const -> const T*
    {
        return &x;
    }
};

template<typename T>
struct Vertex3
{
    Vector3<T> vertex;
    Vector3<T> normal;
};

template<typename T>
struct Vertices3
{
    std::vector<Vertex3<T>> vertices;
    std::vector<size_t> indices;
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

using Vector4f = Vector4<float>;

using Vertex3f = Vertex3<float>;
using Vertices3f = Vertices3<float>;

namespace vec
{

template<typename T>
constexpr auto UP = Vector3<T>{static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)};

template<typename T>
constexpr auto DOWN = Vector3<T>{static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0)};

template<typename T>
constexpr auto LEFT = Vector3<T>{static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0)};

template<typename T>
constexpr auto RIGHT = Vector3<T>{static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)};

template<typename T>
constexpr auto FORWARD = Vector3<T>{static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)};

template<typename T>
constexpr auto BACK = Vector3<T>{static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1)};

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
constexpr auto multiply(Vector4<T> v1, T value) noexcept -> Vector4<T>
{
    return {v1.x * value, v1.y * value, v1.z * value, v1.w * value};
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
constexpr auto vec3from(Vector4<T> v1) -> Vector3<T>
{
    return {
        v1.x, v1.y, v1.z
    };
}

template<typename T>
constexpr auto vec4from(Vector3<T> v1, T w = static_cast<T>(1)) -> Vector4<T>
{
    return {
        v1.x, v1.y, v1.z, w
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

inline auto draw(Vector3f start, Vector3f direction) -> void
{
    glBegin(GL_LINES);
    glVertex3fv(start.toBytes());
    glVertex3fv(vec::add(start, direction).toBytes());
    glEnd();
}


}

}

