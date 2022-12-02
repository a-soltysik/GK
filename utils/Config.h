#pragma once

#include "Singleton.h"
#include "math/Types.h"

namespace gk::utils
{

class Config : public Singleton<Config>
{
public:
    enum class Dimensions
    {
        _2D,
        _3D
    };

    Vector3f velocity = {2.5f, 2.5f, 2.5f};
    GLFWwindow* window = nullptr;
    Dimensions dimensions = Dimensions::_3D;
};

}
