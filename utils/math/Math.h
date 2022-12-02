#pragma once

#include <concepts>
#include <numbers>

#include "Types.h"

namespace gk
{

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

namespace utils
{

template<Arithmetic T>
auto toDegrees(T radians)
{
    return static_cast<T>(static_cast<double>(radians) * 180.0 / std::numbers::pi);
}

template<Arithmetic T>
auto toRadians(T degrees)
{
    return static_cast<T>(static_cast<double>(degrees) * std::numbers::pi / 180.0);
}

template<Arithmetic T>
auto normal(Vector3<T> v1, Vector3<T> v2, Vector3<T> v3) -> Vector3<T>
{
    return vec::normalized(vec::cross(vec::subtract(v2, v1), vec::subtract(v3, v1)));
}

template <Arithmetic T>
int32_t sgn(T val) {
    return (static_cast<T>(0) < val) - (val < static_cast<T>(0));
}

}}