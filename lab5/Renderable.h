#pragma once

#include "math/Types.h"
#include "Material.h"

namespace gk::lab5
{

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual auto render(double time) -> void = 0;
    virtual auto renderNormals() -> void = 0;
};


}
