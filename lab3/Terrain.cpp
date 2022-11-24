#include <GLFW/glfw3.h>

#include <cmath>
#include <numbers>
#include <iostream>

#include "Terrain.h"
#include "FastNoise/FastNoise.h"

namespace gk::lab3
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
                       utils::Dimensions::_2D,
                       vsync);
}

auto Terrain::startup() const -> void
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Terrain::shutdown() -> void
{

}

auto Terrain::render([[maybe_unused]] double time) -> void
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    utils::spin(static_cast<float>(glfwGetTime() / 25.0 * 180.0 / std::numbers::pi));
    utils::axes(50, 50, 50);
    makeTerrain();
    glFlush();
}

auto Terrain::makeTerrain() const -> void
{
    const auto vertices = makeTerrainVertices(resolution);

    for (auto i = size_t{}; i < vertices.size() - 1; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        for (auto j = size_t{}; j < vertices.size(); j++)
        {
            glColor3fv(vertices[i][j].second.toBytes());
            glVertex3fv(vertices[i][j].first.toBytes());

            glColor3fv(vertices[i + 1][j].second.toBytes());
            glVertex3fv(vertices[i + 1][j].first.toBytes());
        }
        glEnd();
    }

}

auto Terrain::makeTerrainVertices(size_t N) -> std::vector<std::vector<std::pair<Vector3f, Color3f>>>
{
    static auto vertices = std::vector(N, std::vector(N, std::pair<Vector3f, Color3f>{}));
    static auto simplex = FastNoise::New<FastNoise::Simplex>();
    for (auto i = size_t{}; i < N; i++)
    {
        for (auto j = size_t{}; j < N; j++)
        {
            const auto nx = static_cast<float>(i) / static_cast<float>(N - 1) * scale + static_cast<float>(glfwGetTime()) * velocity;
            const auto ny = static_cast<float>(j) / static_cast<float>(N - 1) * scale + static_cast<float>(glfwGetTime()) * velocity;
            vertices[i][j].first.x = std::lerp(-terrainBounds.x, terrainBounds.x, static_cast<float>(i) / static_cast<float>(N - 1));
            vertices[i][j].first.y = simplex->GenSingle2D(nx * frequency, ny * frequency, 0) * heightScale;
            vertices[i][j].first.z = std::lerp(-terrainBounds.y, terrainBounds.y, static_cast<float>(j) / static_cast<float>(N - 1));

            const auto colorValue = std::lerp(0.f, 1.f, 0.5f + vertices[i][j].first.y / (2.f * heightScale));
            vertices[i][j].second = {colorValue, colorValue, colorValue};
        }
    }
    return vertices;
}

}

