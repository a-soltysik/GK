#pragma once

#include "keyboard/SceneMovementHandler.h"
#include "mouse/SceneScaleMouseHandler.h"
#include "mouse/SceneRotationMouseHandler.h"
#include "Camera.h"

namespace gk::utils
{

class BasicCameraHandler
{
public:
    explicit BasicCameraHandler(const Camera& camera);
    BasicCameraHandler(const BasicCameraHandler&) = delete;
    BasicCameraHandler(BasicCameraHandler&&) = default;
    BasicCameraHandler& operator=(const BasicCameraHandler&) = delete;
    BasicCameraHandler& operator=(BasicCameraHandler&&) = default;
    ~BasicCameraHandler() = default;

    auto getCameraState(double time) -> Camera;

    auto pause() -> void;
    auto start() -> void;

private:
    static auto calculateOffset(const Camera& camera) -> Vector2f;
    auto getCameraDirection() -> Vector3f;

    [[nodiscard]]
    auto getVelocity() const -> Vector3f;

    Camera camera;
    Vector2f angleOffset;
    SceneRotationMouseHandler rotationHandler;
    bool isPaused = false;
};

}
