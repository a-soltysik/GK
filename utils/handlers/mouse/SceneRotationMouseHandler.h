#pragma once

#include "math/Types.h"

namespace gk::utils
{

class SceneRotationMouseHandler
{
public:
    SceneRotationMouseHandler();
    SceneRotationMouseHandler(Vector2d min, Vector2d max);
    [[nodiscard]] auto getSceneRotationInDegrees() const -> Vector2d;
    auto reset() -> void;

private:
    auto registerCallbacks(Vector2d min, Vector2d max) -> void;

    bool isLeftMouseButtonPressed = false;
    Vector2d angles = {};
    Vector2d lastPosition = {};
};

}