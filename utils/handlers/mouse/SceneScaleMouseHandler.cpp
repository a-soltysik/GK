#include "SceneScaleMouseHandler.h"
#include "MouseHandler.h"

namespace gk::utils
{

SceneScaleMouseHandler::SceneScaleMouseHandler()
{
    MouseHandler::instance().addMouseButtonCallback([this](auto, auto button, auto action, auto) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            isRightMouseButtonPressed = true;
        }
        else
        {
            isRightMouseButtonPressed = false;
        }
    });
    MouseHandler::instance().addMouseMotionCallback([this](auto, double x, double y) {
        if (isRightMouseButtonPressed && !isPaused)
        {
            scale = std::max(scale + (y - lastPosition.y) / 100.0, 0.1);
        }
        lastPosition = {x, y};
    });
}

auto SceneScaleMouseHandler::getSceneScale() const -> double
{
    return scale;
}

auto SceneScaleMouseHandler::reset() -> void
{
    scale = 1.0;
}

auto SceneScaleMouseHandler::pause() -> void
{
    isPaused = true;
}

auto SceneScaleMouseHandler::start() -> void
{
    isPaused = false;
}

}

