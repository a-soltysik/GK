#include <GLFW/glfw3.h>

#include <cmath>
#include <numbers>

#include "Egg.h"

namespace gk::lab4
{

Egg::Egg(uint32_t resolution)
    : vertices(makeEggVertices(resolution))
{

}

auto Egg::render([[maybe_unused]] double time) -> void
{
    makeEgg();
}

auto Egg::makeEgg() -> void
{
    glBegin(GL_TRIANGLE_STRIP);
    for (auto i = size_t {}; i < vertices.size() - 1; i++)
    {
        for (auto j = size_t {}; j < vertices.size(); j++)
        {
            glColor3fv(vertices[i][j].second.toBytes());
            glVertex3fv(vertices[i][j].first.toBytes());

            glColor3fv(vertices[i + 1][j].second.toBytes());
            glVertex3fv(vertices[i + 1][j].first.toBytes());
        }
    }
    glEnd();
}

auto Egg::makeEggVertices(size_t N) -> std::vector<std::vector<std::pair<Vector3f, Color3f>>>
{
    static auto vertices = std::vector(N, std::vector(N, std::pair<Vector3f, Color3f>{}));

    for (auto i = size_t {}; i < N; i++)
    {
        for (auto j = size_t {}; j < N; j++)
        {
            const auto u = static_cast<float>(i) / static_cast<float>(N - 1);
            const auto v = static_cast<float>(j) / static_cast<float>(N - 1);
            vertices[i][j].first.x = static_cast<float>(
                (-90. * std::pow(u, 5) + 225. * std::pow(u, 4) - 270. * std::pow(u, 3) + 180. * std::pow(u, 2) -
                 45. * u) * std::cos(std::numbers::pi * v));
            vertices[i][j].first.y = static_cast<float>(160. * std::pow(u, 4) - 320. * std::pow(u, 3) +
                                                        160. * std::pow(u, 2) - 5.);
            vertices[i][j].first.z = static_cast<float>(
                (-90. * std::pow(u, 5) + 225. * std::pow(u, 4) - 270. * std::pow(u, 3) + 180. * std::pow(u, 2) -
                 45. * u) * std::sin(std::numbers::pi * v));

            const auto colorVal = std::lerp(0.f, 1.f, u);
            vertices[i][j].second = {0.5f, colorVal, 0.7f};
        }
    }
    return vertices;
}

}

