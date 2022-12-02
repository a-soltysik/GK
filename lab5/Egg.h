#pragma once

#include <vector>

#include "Utils.h"
#include "Renderable.h"

namespace gk::lab5
{

class Egg : public Renderable
{
public:
    explicit Egg(uint32_t resolution);
    auto render(double time) -> void override;
    auto renderNormals() -> void override;

private:
    auto makeVertices(uint32_t resolution) -> void;
    static auto getNormal(float u, float v) -> Vector3f;

    std::vector<std::vector<Vertex3f>> vertices;
    gfx::Material material;
};

}
