#pragma once

#include "Utils.h"

namespace gk::lab2
{

class Rectangle
{
public:
    auto run(Vector2i dimensions, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render(double) -> void;
    static auto makeRectangle(Vector2f center, Vector2f sides, float distortionFactor) -> void;

    static constexpr auto bounds = Vector2f {100.f, 100.f};
    static constexpr auto nearDepth = 100.f;
    static constexpr auto farDepth = -100.f;

    Vector2i dimensions;
};

}
