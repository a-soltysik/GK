#pragma once

#include <memory>

#include "Renderable.h"
#include "Utils.h"
#include "Handlers/Mouse/SceneScaleMouseHandler.h"
#include "Handlers/Keyboard/SceneMovementHandler.h"

namespace gk::lab4
{

class Renderer
{
public:
    auto setObject(std::unique_ptr<Renderable> newObject) -> void;
    auto run(Vector2i dimensions, bool vsync = false) -> void;

private:
    auto startup() const -> void;
    auto shutdown() -> void;
    auto render(double time) -> void;
    auto freeMove(double time) -> void;
    auto moveAround() -> void;

    // Free roam
    static auto getCameraDirection() -> Vector3f;
    auto getVelocity(Vector3f cameraFront, Vector3f cameraUp) -> Vector3f;

    // Move around
    auto rotateAroundGlStyle() -> void;
    auto rotateAroundManually() -> void;
    auto getCameraPosition(Vector3f center) -> std::pair<Vector3f, Vector3f>;

    static constexpr auto bounds = Vector2f {7.5f, 7.5f};
    static constexpr auto nearDepth = 8.f;
    static constexpr auto farDepth = -8.f;

    utils::SceneScaleMouseHandler scaleHandler;
    std::unique_ptr<Renderable> object;
    Vector3f camera = {0.f, 0.f, 10.f};
    Vector2i dimensions;

    bool freeRoam = false;
};

}