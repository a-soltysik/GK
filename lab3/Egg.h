#pragma once

#include <vector>

#include "Utils.h"

namespace gk::lab3
{

class Egg
{
public:
    auto run(Vector2i dimensions, uint32_t resolution, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render() -> void;
    auto makeEgg() -> void;
    static auto makeEggVertices(size_t N) -> std::vector<std::vector<std::pair<Vector3f, Color3f>>>;

    static constexpr auto bounds = Vector2f {7.5f, 7.5f};
    static constexpr auto nearDepth = 8.f;
    static constexpr auto farDepth = -8.f;

    Vector2i dimensions;
    std::vector<std::vector<std::pair<Vector3f, Color3f>>> vertices;
};

}
