#pragma once

#include <unordered_set>

#include "KeyboardHandler.h"

namespace gk::utils
{

class SceneMovementHandler
{
public:
    SceneMovementHandler();
    [[nodiscard]] auto getSceneMovement() const -> Vector3f;
private:
    std::unordered_set<int> keysDown;
};

}