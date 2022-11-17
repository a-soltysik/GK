#include <GLFW/glfw3.h>
#include <array>

#include "Rectangle.h"

namespace gk
{

auto Rectangle::run(Vector2i dimensions, bool vsync) -> void
{
    this->dimensions = dimensions;
    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       vsync);
}

auto Rectangle::startup() const -> void
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Rectangle::shutdown() -> void
{

}

auto Rectangle::render([[maybe_unused]] double time) -> void
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeRectangle({0.f, 0.f}, {150.f, 100.f}, 0.5f);
    glFlush();
}

auto Rectangle::makeRectangle(Vector2f center, Vector2f sides, float distortionFactor) -> void
{
    glBegin(GL_TRIANGLE_FAN);

    glColor3ub(123, 200, 76);

    auto distortions = std::array<float, 4> {};
    for (auto& distortion : distortions)
    {
        distortion = 1 + (utils::getRandom(0.f, 1.f) * (utils::getRandom(0.f, 1.f) < 0.5f ? 1.f : -1.f)) * distortionFactor;
    }

    glVertex2f(center.x - (sides.x / 2.f) * distortions[0], center.y + (sides.y / 2.f) * distortions[0]);
    glVertex2f(center.x + (sides.x / 2.f) * distortions[1], center.y + (sides.y / 2.f) * distortions[1]);
    glVertex2f(center.x + (sides.x / 2.f) * distortions[2], center.y - (sides.y / 2.f) * distortions[2]);
    glVertex2f(center.x - (sides.x / 2.f) * distortions[3], center.y - (sides.y / 2.f) * distortions[3]);

    glEnd();
}

}

