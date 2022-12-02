#pragma once

#include <unordered_set>

#include "KeyboardHandler.h"

namespace gk::utils
{

class SceneMovementHandler : public Singleton<SceneMovementHandler>
{
public:
    [[nodiscard]] auto getSceneMovement() const -> Vector3f;

private:
    SceneMovementHandler();
    std::unordered_set<int> keysDown;

    friend class Singleton<SceneMovementHandler>;
};

}