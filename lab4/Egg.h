#pragma once

#include <vector>

#include "Utils.h"
#include "Renderable.h"

namespace gk::lab4
{

class Egg : public Renderable
{
public:
    explicit Egg(uint32_t resolution);
    auto render([[maybe_unused]] double time) -> void override;

private:
    auto makeEgg() -> void;
    static auto makeEggVertices(size_t N) -> std::vector<std::vector<std::pair<Vector3f, Color3f>>>;

    const std::vector<std::vector<std::pair<Vector3f, Color3f>>> vertices;
};

}
