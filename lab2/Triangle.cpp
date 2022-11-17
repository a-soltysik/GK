#include <GLFW/glfw3.h>
#include <numbers>

#include "Triangle.h"

namespace gk
{

auto Triangle::run(Vector2i dimensions, bool vsync) -> void
{
    this->dimensions = dimensions;
    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       vsync);
}

auto Triangle::startup() -> void
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Triangle::shutdown() -> void
{

}

auto Triangle::render([[maybe_unused]] double time) -> void
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeTriangle(200.f);
    glFlush();
}

auto Triangle::makeTriangle(float side) -> void
{
    const auto height = side * std::numbers::sqrt3_v<float> / 2.f;

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(-side / 2.f, -height / 2.f);

    glColor3f(0.f, 1.f, 0.f);
    glVertex2f(side / 2.f, -height / 2.f);

    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(0.f, height / 2.f);
    glEnd();
}

}

