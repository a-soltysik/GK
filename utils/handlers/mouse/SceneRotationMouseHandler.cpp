#include "SceneRotationMouseHandler.h"
#include "MouseHandler.h"

namespace gk::utils
{

SceneRotationMouseHandler::SceneRotationMouseHandler()
{
    registerCallbacks({std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
                      {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()});
}

SceneRotationMouseHandler::SceneRotationMouseHandler(Vector2d min, Vector2d max)
{
    registerCallbacks(min, max);
}

auto SceneRotationMouseHandler::getSceneRotationInDegrees() const -> Vector2d
{
    return angles;
}

auto SceneRotationMouseHandler::reset() -> void
{
    angles = {};
}

auto SceneRotationMouseHandler::registerCallbacks(Vector2d min, Vector2d max) -> void
{
    MouseHandler::instance().addMouseButtonCallback([this](auto, auto button, auto action, auto) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            isLeftMouseButtonPressed = true;
        }
        else
        {
            isLeftMouseButtonPressed = false;
        }
    });
    MouseHandler::instance().addMouseMotionCallback([this, min, max](auto, double x, double y) {
        if (isLeftMouseButtonPressed && !isPaused)
        {
            const auto ratio = MouseHandler::getPixelsToAngleRatio();
            angles = {angles.x + (y - lastPosition.y) * ratio.x, angles.y + (x - lastPosition.x) * ratio.y};

            angles.x = std::min(angles.x, max.x);
            angles.x = std::max(angles.x, min.x);
            angles.y = std::min(angles.y, max.y);
            angles.y = std::max(angles.y, min.y);
        }
        lastPosition = {x, y};
    });
}

auto SceneRotationMouseHandler::pause() -> void
{
    isPaused = true;
}

auto SceneRotationMouseHandler::start() -> void
{
    isPaused = false;
}

}

