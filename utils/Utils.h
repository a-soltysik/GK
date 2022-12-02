#pragma once

#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif

#include <GLFW/glfw3.h>

#include <concepts>
#include <random>

#include "Clock.h"
#include "Handlers/Mouse/MouseHandler.h"
#include "Handlers/Keyboard/KeyboardHandler.h"
#include "Config.h"

namespace gk::utils
{

auto configureViewport(Vector2f bounds, float nearDepth = 100.f, float farDepth = -100.f) -> void;
auto viewport(GLFWwindow* window, int width, int height) -> void;
auto makeWindow(Vector2i size, bool vsync) -> GLFWwindow*;
auto axes(float x, float y, float z) -> void;
auto spin(float angle) -> void;

auto defaultInit(Vector2i size,
                 std::invocable auto startup,
                 std::invocable<double> auto render,
                 std::invocable auto shutdown,
                 Config::Dimensions dimensions,
                 bool vsync = false) -> void
{
    auto* window = makeWindow(size, vsync);
    Config::instance().window = window;
    Config::instance().dimensions = dimensions;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseMotionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

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

template<class... Ts> struct match : Ts... { using Ts::operator()...; };
template<class... Ts> match(Ts...) -> match<Ts...>;

}
