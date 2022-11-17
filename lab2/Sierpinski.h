#pragma once

#include <array>

#include "Utils.h"

namespace gk
{

class Sierpinski
{
public:
    auto run(Vector2i dimensions, uint32_t level, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render(double) -> void;
    auto makeSierpinskiCarpet(Vector2f center, Vector2f sides, uint32_t currentLevel) -> void;
    static auto makeRectangle(Vector2f center, Vector2f sides, std::array<uint8_t, 3> color) -> void;

    static constexpr auto bounds = Vector2f {100.f, 100.f};
    static constexpr auto nearDepth = 100.f;
    static constexpr auto farDepth = -100.f;

    Vector2i dimensions;
    uint32_t level;
};

}
