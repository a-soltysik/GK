#pragma once

#include "math/Types.h"

namespace gk::utils
{

class SceneScaleMouseHandler
{
public:
    SceneScaleMouseHandler();
    [[nodiscard]] auto getSceneScale() const -> double;
    auto reset() -> void;

private:
    bool isRightMouseButtonPressed = false;
    double scale = 1.0;
    Vector2d lastPosition = {};
};

}