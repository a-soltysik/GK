#pragma once

#include <concepts>
#include <numbers>

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

}}