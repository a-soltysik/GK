#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GLFW/glfw3.h>

#include <cmath>
#include <numbers>

#include "Egg.h"
#include "math/Math.h"
#include "TextureCacher.h"

namespace gk::lab6
{

Egg::Egg(uint32_t resolution)
    : material {gfx::makeMaterial(Vector3f {0.5f, 0.5f, 0.5f}, Vector3f {0.1f, 0.8f, 1.f}, 20.f)}
    , texture { TextureCacher::instance().loadTexture("textures/earth.tga")}
    , state { Earth{}}
{
    makeVertices(resolution);
}

auto Egg::startup() -> void
{
    utils::KeyboardHandler::instance().addKeyCallback([this](auto*, auto key, auto, auto action, auto) {
        if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        {
            const auto result = std::visit(utils::match {
                [](Earth&) {
                    return std::make_pair(std::variant<Earth, Jupiter>{Jupiter{}},
                                          TextureCacher::instance().loadTexture("textures/jupiter.tga"));
                },
                [](Jupiter&) {
                    return std::make_pair(std::variant<Earth, Jupiter>{Earth{}},
                                          TextureCacher::instance().loadTexture("textures/earth.tga"));
                }
            }, state);
            state = result.first;
            texture = result.second;
        }
    });
}

auto Egg::makeVertices(uint32_t resolution) -> void
{
    vertices = std::vector(resolution, std::vector(resolution, Vertex3f {}));

    for (auto i = size_t {}; i < resolution; i++)
    {
        for (auto j = size_t {}; j < resolution; j++)
        {
            const auto u = static_cast<float>(i) / static_cast<float>(resolution - 1);
            const auto v = static_cast<float>(j) / static_cast<float>(resolution - 1);

            vertices[i][j].vertex.x =
                static_cast<float>((-90. * std::pow(u, 5) +
                                    225. * std::pow(u, 4) -
                                    270. * std::pow(u, 3) +
                                    180. * std::pow(u, 2) -
                                    45. * u) * std::cos(std::numbers::pi * v));

            vertices[i][j].vertex.y =
                static_cast<float>(160. * std::pow(u, 4) -
                                   320. * std::pow(u, 3) +
                                   160. * std::pow(u, 2) - 5.);

            vertices[i][j].vertex.z =
                static_cast<float>((-90. * std::pow(u, 5) +
                                    225. * std::pow(u, 4) -
                                    270. * std::pow(u, 3) +
                                    180. * std::pow(u, 2) -
                                    45. * u) * std::sin(std::numbers::pi * v));

            if (vertices[i][j].vertex.z <= 0.f)
            {
                vertices[i][j].normal = getNormal(u, v);
            }
            else
            {
                vertices[i][j].normal = vec::multiply(getNormal(u, v), -1.f);
            }
        }
    }
}

auto Egg::getNormal(float u, float v) -> Vector3f
{
    const auto xu = static_cast<float>((-450. * std::pow(u, 4)
                                        + 900. * std::pow(u, 3)
                                        - 810. * std::pow(u, 2)
                                        + 360. * u
                                        - 45.) * std::cos(std::numbers::pi * v));

    const auto xv = static_cast<float>(std::numbers::pi *
                                       (90. * std::pow(u, 5)
                                        - 225 * std::pow(u, 4)
                                        + 270. * std::pow(u, 3)
                                        - 180. * std::pow(u, 2)
                                        + 45. * u) * std::sin(std::numbers::pi * v));

    const auto yu = static_cast<float>(640. * std::pow(u, 3)
                                       - 960. * std::pow(u, 2)
                                       + 320. * u);
    const auto yv = 0.f;

    const auto zu = static_cast<float>((-450. * std::pow(u, 4)
                                        + 900. * std::pow(u, 3)
                                        - 810. * std::pow(u, 2)
                                        + 360. * u
                                        - 45.) * std::sin(std::numbers::pi * v));

    const auto zv = static_cast<float>(-std::numbers::pi *
                                       (90. * std::pow(u, 5)
                                        - 225 * std::pow(u, 4)
                                        + 270. * std::pow(u, 3)
                                        - 180. * std::pow(u, 2)
                                        + 45. * u) * std::cos(std::numbers::pi * v));

    return vec::normalized(Vector3f {
        yu * zv - zu * yv,
        zu * xv - xu * zv,
        xu * yv - yu * xv
    });
}

auto Egg::render([[maybe_unused]] double time) -> void
{
    material.prepareMaterial();
    texture->prepareTexture();

    for (auto i = size_t {}; i < vertices.size() - 1; i++)
    {
        const auto u = static_cast<float>(i) / static_cast<float>(vertices.size() - 1);
        const auto u2 = static_cast<float>(i + 1) / static_cast<float>(vertices.size() - 1);

        glBegin(GL_TRIANGLE_STRIP);
        for (auto j = size_t {}; j < vertices.size(); j++)
        {
            auto v = static_cast<float>(j) / static_cast<float>(vertices.size() - 1);

            if (vertices[i + 1][j].vertex.z >= 0.f)
            {
                glTexCoord2f(1.f - v / 2.f, 1.f - u * 2.f);
                glNormal3fv(vertices[i][j].normal.toBytes());
                glVertex3fv(vertices[i][j].vertex.toBytes());

                glTexCoord2f(1.f - v / 2.f, 1.f - u2 * 2.f);
                glNormal3fv(vertices[i + 1][j].normal.toBytes());
                glVertex3fv(vertices[i + 1][j].vertex.toBytes());
            }
        }
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
        for (auto j = size_t {}; j < vertices.size(); j++)
        {
            auto v = static_cast<float>(j) / static_cast<float>(vertices.size() - 1);

            if (vertices[i][j].vertex.z <= 0.f)
            {
                glTexCoord2f(0.5f - v / 2.f, u2 * 2.f);
                glNormal3fv(vertices[i + 1][j].normal.toBytes());
                glVertex3fv(vertices[i + 1][j].vertex.toBytes());

                glTexCoord2f(0.5f - v / 2.f, u * 2.f);
                glNormal3fv(vertices[i][j].normal.toBytes());
                glVertex3fv(vertices[i][j].vertex.toBytes());
            }
        }
        glEnd();
    }

}

auto Egg::renderNormals() -> void
{
    material.prepareMaterial();
    for (auto i = size_t {}; i < vertices.size() - 1; i++)
    {
        for (auto j = size_t {}; j < vertices.size(); j++)
        {
            vec::draw(vertices[i][j].vertex, vertices[i][j].normal);
        }
    }
}

}

