#pragma once

#include <memory>

#include "Scene.h"

namespace gk::lab6
{

class Renderer
{
public:
    Renderer() = default;
    auto setScene(std::unique_ptr<Scene> newScene) -> void;
    auto run(Vector2i dimensions, bool vsync = false) -> void;

private:
    auto startup() -> void;
    auto shutdown() -> void;
    auto render(double time) -> void;

    static constexpr auto bounds = Vector2f {7.5f, 7.5f};
    static constexpr auto nearDepth = 8.f;
    static constexpr auto farDepth = -8.f;

    std::unique_ptr<Scene> scene;
    Vector2i dimensions{};
};

}