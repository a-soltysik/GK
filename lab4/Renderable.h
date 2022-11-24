#pragma once

namespace gk::lab4
{

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual auto render(double time) -> void = 0;
};

}
