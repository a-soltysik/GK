#pragma once

#include <vector>

#include "math/Types.h"

namespace gk::gfx
{

struct Texture
{
    uint32_t width;
    uint32_t height;
    GLint internalFormat;
    GLenum format;
    std::vector<uint8_t> data;

    auto prepareTexture() const -> void
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     internalFormat,
                     static_cast<GLsizei>(width),
                     static_cast<GLsizei>(height),
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     data.data()
        );
    }
};

}
