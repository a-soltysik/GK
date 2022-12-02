#pragma once

#include "math/Types.h"

namespace gk::utils
{

class SceneScaleMouseHandler
{
public:
    SceneScaleMouseHandler();
    SceneScaleMouseHandler(const SceneScaleMouseHandler&) = delete;
    SceneScaleMouseHandler(SceneScaleMouseHandler&&) = default;
    SceneScaleMouseHandler& operator=(const SceneScaleMouseHandler&) = delete;
    SceneScaleMouseHandler& operator=(SceneScaleMouseHandler&&) = default;
    ~SceneScaleMouseHandler() = default;

    [[nodiscard]] auto getSceneScale() const -> double;
    auto reset() -> void;
    auto pause() -> void;
    auto start() -> void;

private:
    bool isRightMouseButtonPressed = false;
    bool isPaused = false;
    double scale = 1.0;
    Vector2d lastPosition = {};
};

}