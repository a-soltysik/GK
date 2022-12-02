#pragma once

#include "Utils.h"

namespace gk::lab2
{

class Mandelbrot
{
public:
    auto run(Vector2i dimensions, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render(double) -> void;
    auto makeMandelbrotSet(Vector2f topLeft, Vector2f bottomRight) const -> void;
    static auto isConvergent(Vector2f point, uint32_t maxSteps) -> bool;

    static constexpr auto nearDepth = 100.f;
    static constexpr auto farDepth = -100.f;

    Vector2f bounds;
    Vector2i dimensions;
};

}
