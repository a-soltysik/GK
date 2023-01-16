#pragma once

#include "math/Types.h"
#include "Material.h"

namespace gk::lab6
{

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual auto startup() -> void {};
    virtual auto render(double time) -> void = 0;
    virtual auto renderNormals() -> void = 0;
};


}
