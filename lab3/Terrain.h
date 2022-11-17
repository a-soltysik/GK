#pragma once

#include <vector>

#include "Utils.h"

namespace gk
{

class Terrain
{
public:
    auto run(Vector2i dimensions, uint32_t resolution, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render(double time) -> void;
    auto makeTerrain() -> void;
    static auto makeTerrainVertices(size_t N) -> std::vector<std::vector<std::vector<float>>>;

    static constexpr auto bounds = Vector2f {100.f, 100.f};
    static constexpr auto nearDepth = 100.f;
    static constexpr auto farDepth = -100.f;

    static constexpr auto terrainBounds = Vector2f{ 90.f, 90.f };
    static constexpr auto scale = 8.f;
    static constexpr auto frequency = 0.8f;
    static constexpr auto heightScale = 10.f;
    static constexpr auto velocity = 0.3f;

    Vector2i dimensions;
    uint32_t resolution;
};

}
