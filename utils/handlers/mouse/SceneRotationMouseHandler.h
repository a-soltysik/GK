#pragma once

#include "math/Types.h"

namespace gk::utils
{

class SceneRotationMouseHandler
{
public:
    SceneRotationMouseHandler();
    SceneRotationMouseHandler(const SceneRotationMouseHandler&) = delete;
    SceneRotationMouseHandler(SceneRotationMouseHandler&&) = default;
    SceneRotationMouseHandler& operator=(const SceneRotationMouseHandler&) = delete;
    SceneRotationMouseHandler& operator=(SceneRotationMouseHandler&&) = default;
    ~SceneRotationMouseHandler() = default;

    SceneRotationMouseHandler(Vector2d min, Vector2d max);
    [[nodiscard]] auto getSceneRotationInDegrees() const -> Vector2d;
    auto reset() -> void;
    auto pause() -> void;
    auto start() -> void;

private:
    auto registerCallbacks(Vector2d min, Vector2d max) -> void;

    bool isLeftMouseButtonPressed = false;
    bool isPaused = false;
    Vector2d angles = {};
    Vector2d lastPosition = {};
};

}