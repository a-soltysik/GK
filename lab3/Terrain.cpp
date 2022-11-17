#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "Terrain.h"
#include "Noise.h"

namespace gk
{

auto Terrain::run(Vector2i dimensions, uint32_t resolution, bool vsync) -> void
{
    this->dimensions = dimensions;
    this->resolution = resolution;
    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       vsync);
}

auto Terrain::startup() -> void
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Terrain::shutdown() -> void
{

}

auto Terrain::render(double time) -> void
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    utils::spin(static_cast<float>(glfwGetTime() / 25.0 * 180.0 / std::numbers::pi));
    utils::axes(50, 50, 50);
    makeTerrain();
    glFlush();
}

auto Terrain::makeTerrain() -> void
{
    const auto vertices = makeTerrainVertices(resolution);

    for (auto i = size_t{}; i < vertices.size() - 1; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3ub(255, 128, 170);

        for (auto j = size_t{}; j < vertices.size(); j++)
        {
            glVertex3fv(vertices[i][j].data());
            glVertex3fv(vertices[i + 1][j].data());
        }
        glEnd();
    }

}

auto Terrain::makeTerrainVertices(size_t N) -> std::vector<std::vector<std::vector<float>>>
{
    static auto vertices = std::vector<std::vector<std::vector<float>>>(N, std::vector<std::vector<float>>(N, std::vector<float>(3, 0.f)));
    static auto noise = utils::Noise<float>{};
    for (auto i = size_t{}; i < N; i++)
    {
        for (auto j = size_t{}; j < N; j++)
        {
            const auto nx = static_cast<float>(i) / static_cast<float>(N - 1) * scale + static_cast<float>(glfwGetTime()) * velocity;
            const auto ny = static_cast<float>(j) / static_cast<float>(N - 1) * scale + static_cast<float>(glfwGetTime()) * velocity;
            vertices[i][j][0] = std::lerp(-terrainBounds.x, terrainBounds.x, static_cast<float>(i) / static_cast<float>(N - 1));
            vertices[i][j][1] = static_cast<float>(noise.octave2D(nx * frequency, ny * frequency, 3)) * heightScale;
            vertices[i][j][2] = std::lerp(-terrainBounds.y, terrainBounds.y, static_cast<float>(j) / static_cast<float>(N - 1));
        }
    }
    return vertices;
}

}

