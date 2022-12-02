#pragma once

#include "math/Types.h"

namespace gk::gfx
{

struct Material
{
    Vector4f ambient;
    Vector4f diffuse;
    Vector4f specular;
    float shininess;

    auto prepareMaterial() const -> void
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.toBytes());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.toBytes());
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular.toBytes());
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
};

inline auto makeMaterial(Vector3f color, Vector3f multiplier, float shininess) -> Material
{
    return {
        .ambient = vec::vec4from(vec::multiply(color, multiplier.x)),
        .diffuse = vec::vec4from(vec::multiply(color, multiplier.y)),
        .specular = vec::vec4from(vec::multiply(color, multiplier.z)),
        .shininess = shininess
    };
}

}
