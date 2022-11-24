#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <functional>

#include "math/Types.h"
#include "Singleton.h"


namespace gk::utils
{

class MouseHandler : public Singleton<MouseHandler>
{
public:
    using ButtonCallback = std::function<void(GLFWwindow*, int, int, int)>;
    using MotionCallback = std::function<void(GLFWwindow*, double, double)>;

    auto addMouseButtonCallback(ButtonCallback callback) -> void;
    auto addMouseMotionCallback(MotionCallback callback) -> void;
    auto setMouseMoveToAngleRatio(double ratio) -> void;
    [[nodiscard]] auto mouseMoveToAngle() const -> Vector2d;

    auto getPosition() -> Vector2d;
    auto getDeltaPosition() -> Vector2d;
    static auto getPixelsToAngleRatio() -> Vector2d;

    friend auto mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void;
    friend auto mouseMotionCallback(GLFWwindow* window, double x, double y) -> void;

private:
    friend class Singleton<MouseHandler>;

    MouseHandler();

    std::vector<ButtonCallback> mouseButtonCallbacks;
    std::vector<MotionCallback> mouseMotionCallbacks;

    Vector2d mousePosition{};
    Vector2d deltaMouse{};
    double mouseMoveToAngleRatio{};
};

auto mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void;
auto mouseMotionCallback(GLFWwindow* window, double x, double y) -> void;

}