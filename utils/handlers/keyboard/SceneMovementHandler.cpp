#include "SceneMovementHandler.h"

namespace gk::utils
{

SceneMovementHandler::SceneMovementHandler()
{
    KeyboardHandler::instance().addKeyCallback([this](auto, auto key, auto, auto action, auto) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            keysDown.insert(key);
        }
        else
        {
            keysDown.erase(key);
        }
    });
}

auto SceneMovementHandler::getSceneMovement() const -> Vector3f
{
    auto direction = Vector3f{};
    for (auto key : keysDown)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            direction.z += 1.f;
            break;
        case GLFW_KEY_S:
            direction.z -= 1.f;
            break;
        case GLFW_KEY_D:
            direction.x += 1.f;
            break;
        case GLFW_KEY_A:
            direction.x -= 1.f;
            break;
        case GLFW_KEY_SPACE:
            direction.y += 1.f;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            direction.y -= 1.f;
            break;
        default:
            break;
        }
    }
    std::clamp(direction.x, -1.f, 1.f);
    std::clamp(direction.y, -1.f, 1.f);
    std::clamp(direction.z, -1.f, 1.f);
    return direction;
}

}

