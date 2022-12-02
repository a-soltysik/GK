#pragma once

#include <array>

#include "math/Types.h"

namespace gk::gfx
{



struct Light
{
    struct Attenuation
    {
        float constant;
        float linear;
        float quadratic;
    };

    static constexpr auto IDS = std::array<GLenum, 8>{
        GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7
    };

    Vector4f    ambient;
    Vector4f    diffuse;
    Vector4f    specular;
    Vector4f    position;
    Attenuation attenuation;

    auto enable(size_t id) const -> void
    {
        if (id >= IDS.size())
        {
            return;
        }

        const auto lightEnum = IDS[id];
        glLightfv(lightEnum, GL_AMBIENT, ambient.toBytes());
        glLightfv(lightEnum, GL_DIFFUSE, diffuse.toBytes());
        glLightfv(lightEnum, GL_SPECULAR, specular.toBytes());
        glLightfv(lightEnum, GL_POSITION, position.toBytes());

        glLightf(lightEnum, GL_CONSTANT_ATTENUATION, attenuation.constant);
        glLightf(lightEnum, GL_LINEAR_ATTENUATION, attenuation.linear);
        glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, attenuation.quadratic);

        glEnable(lightEnum);
    }
};

}

