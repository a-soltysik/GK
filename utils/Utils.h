#pragma once

#include <GLFW/glfw3.h>
#include <concepts>
#include <random>

#include "Clock.h"
#include "Types.h"

namespace gk::utils
{

auto configureViewport(Vector2f bounds, float nearDepth = 100.f, float farDepth = -100.f) -> void;
auto viewport(GLFWwindow* window, int width, int height) -> void;
auto makeWindow(Vector2i dimensions, bool vsync) -> GLFWwindow*;
auto axes(float x, float y, float z) -> void;
auto spin(float angle) -> void;

auto defaultInit(Vector2i dimensions,
                 std::invocable auto startup,
                 std::invocable<double> auto render,
                 std::invocable auto shutdown,
                 bool vsync = false) -> void
{
    auto* window = makeWindow(dimensions, vsync);
    startup();
    auto clock = Clock{};
    while (!glfwWindowShouldClose(window))
    {
        const auto deltaTime = static_cast<double>(clock.getTime<std::chrono::nanoseconds>()) / 1.0e9;
        clock.start();
        render(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents();
        clock.stop();
    }
    shutdown();
    glfwTerminate();
}

template<std::floating_point T>
[[nodiscard]]
auto getRandom(T from, T to) -> T
{
    static auto device = std::random_device {};
    static auto rng    = std::mt19937 {device()};

    if (from > to)
    {
        std::swap(from, to);
    }

    auto distribution = std::uniform_real_distribution {from, to};
    return distribution(rng);
}

}
