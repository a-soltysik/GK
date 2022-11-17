#pragma once

#include "Utils.h"

namespace gk
{

class Triangle
{
public:
    auto run(Vector2i dimensions, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    static auto render(double) -> void;
    static auto makeTriangle(float side) -> void;

    static constexpr auto bounds = Vector2f {100.f, 100.f};
    static constexpr auto nearDepth = 100.f;
    static constexpr auto farDepth = -100.f;

    Vector2i dimensions;
};

}
