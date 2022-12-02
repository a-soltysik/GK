#include "MouseHandler.h"
#include "Utils.h"

namespace gk::utils
{

auto mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void
{
    for (const auto& callback : MouseHandler::instance().mouseButtonCallbacks)
    {
        callback(window, button, action, mods);
    }
}

auto MouseHandler::addMouseButtonCallback(ButtonCallback callback) -> void
{
    mouseButtonCallbacks.push_back(std::move(callback));
}

auto MouseHandler::setMouseMoveToAngleRatio(double ratio) -> void
{
    mouseMoveToAngleRatio = ratio;
}

auto MouseHandler::mouseMoveToAngle() const -> Vector2d
{
    return {deltaMouse.y * mouseMoveToAngleRatio, deltaMouse.x * mouseMoveToAngleRatio};
}

auto MouseHandler::addMouseMotionCallback(MotionCallback callback) -> void
{
    mouseMotionCallbacks.push_back(std::move(callback));
}

auto mouseMotionCallback(GLFWwindow* window, double x, double y) -> void
{
    for (const auto& callback : MouseHandler::instance().mouseMotionCallbacks)
    {
        callback(window, x, y);
    }
}

MouseHandler::MouseHandler()
{
    addMouseMotionCallback([this](GLFWwindow*, double x, double y){
        deltaMouse = {x - mousePosition.x, y - mousePosition.y};
        mousePosition = {x, y};
    });
}

auto MouseHandler::getPosition() -> Vector2d
{
    return mousePosition;
}

auto MouseHandler::getDeltaPosition() -> Vector2d
{
    return deltaMouse;
}

auto MouseHandler::getPixelsToAngleRatio() -> Vector2d
{
    auto width = int{};
    auto height = int{};
    glfwGetWindowSize(Config::instance().window, &width, &height);
    return {360. / height, 360. / width};
}

}
