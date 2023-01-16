#pragma once

#include <vector>
#include <variant>

#include "Utils.h"
#include "Renderable.h"

namespace gk::lab6
{

class Egg : public Renderable
{
public:
    explicit Egg(uint32_t resolution);
    auto startup() -> void override;
    auto render(double time) -> void override;
    auto renderNormals() -> void override;

private:
    auto makeVertices(uint32_t resolution) -> void;
    static auto getNormal(float u, float v) -> Vector3f;

    struct Earth{};
    struct Jupiter{};

    std::vector<std::vector<Vertex3f>> vertices;
    gfx::Material material;
    gfx::Texture* texture;
    std::variant<Earth, Jupiter> state;
};

}
