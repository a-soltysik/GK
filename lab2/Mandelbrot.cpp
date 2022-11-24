#include <GLFW/glfw3.h>
#include <complex>

#include "Mandelbrot.h."

namespace gk::lab3
{

auto Mandelbrot::run(Vector2i dimensions, bool vsync) -> void
{
    this->dimensions = dimensions;
    this->bounds = Vector2f {static_cast<float>(dimensions.x) / 2.f, static_cast<float>(dimensions.y) / 2.f};

    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       utils::Dimensions::_2D,
                       vsync);
}

auto Mandelbrot::startup() const -> void
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Mandelbrot::shutdown() -> void
{

}

auto Mandelbrot::render([[maybe_unused]] double time) -> void
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeMandelbrotSet({-2.f, 1.5f}, {1.f, -1.5f});
    glFlush();
}

auto Mandelbrot::makeMandelbrotSet(Vector2f topLeft, Vector2f bottomRight) const -> void
{
    glColor3ub(56, 127, 230);
    glBegin(GL_POINTS);
    for (auto i = 0; i < dimensions.x; i++)
    {
        for (auto j = 0; j < dimensions.y; j++)
        {
            const auto coord = Vector2f {topLeft.x + (static_cast<float>(i) * (bottomRight.x - topLeft.x) / static_cast<float>(dimensions.x)),
                                         topLeft.y + (static_cast<float>(j) * (bottomRight.y - topLeft.y) / static_cast<float>(dimensions.y))};

            if (isConvergent(coord, 30))
            {
                glVertex2i(i - static_cast<int>(bounds.x), j - static_cast<int>(bounds.y));
            }
        }
    }
    glEnd();
}

auto Mandelbrot::isConvergent(Vector2f point, uint32_t maxSteps) -> bool
{
    auto z = std::complex<float>{};
    const auto p = std::complex{point.x, point.y};
    for (auto i = uint32_t{}; i < maxSteps; i++)
    {
        z = std::pow(z, 2) + p;

        if (std::abs(z) >= 2.f)
        {
            return false;
        }
    }
    return true;
}

}