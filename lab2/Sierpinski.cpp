#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GLFW/glfw3.h>

#include <array>

#include "Sierpinski.h"

namespace gk::lab2
{

auto Sierpinski::run(Vector2i dimensions, uint32_t level, bool vsync) -> void
{
    this->dimensions = dimensions;
    this->level = level;

    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       utils::Config::Dimensions::_2D,
                       vsync);
}

auto Sierpinski::startup() const -> void
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Sierpinski::shutdown() -> void
{

}

auto Sierpinski::render([[maybe_unused]] double time) -> void
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeSierpinskiCarpet({0.f, 0.f}, {200.f, 200.f}, level);
    glFlush();
}

auto Sierpinski::makeSierpinskiCarpet(Vector2f center, Vector2f sides, uint32_t currentLevel) -> void
{
    if (currentLevel == 0)
    {
        return;
    }

    const auto newSides = Vector2f {sides.x / 3.f, sides.y / 3.f};

    makeRectangle(center, sides, {128, 40, 200});
    makeRectangle(center, newSides, {128, 128, 128});

    makeSierpinskiCarpet(Vector2f{center.x - newSides.x, center.y + newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x, center.y + newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x + newSides.x, center.y + newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x + newSides.x, center.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x + newSides.x, center.y - newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x, center.y - newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x - newSides.x, center.y - newSides.y}, newSides, currentLevel - 1);
    makeSierpinskiCarpet(Vector2f{center.x - newSides.x, center.y}, newSides, currentLevel - 1);
}

auto Sierpinski::makeRectangle(Vector2f center, Vector2f sides, std::array<uint8_t, 3> color) -> void
{
    glBegin(GL_TRIANGLE_FAN);

    glColor3ubv(color.data());

    glVertex2f(center.x - (sides.x / 2), center.y + (sides.y / 2));
    glVertex2f(center.x + (sides.x / 2), center.y + (sides.y / 2));
    glVertex2f(center.x + (sides.x / 2), center.y - (sides.y / 2));
    glVertex2f(center.x - (sides.x / 2), center.y - (sides.y / 2));

    glEnd();
}

}