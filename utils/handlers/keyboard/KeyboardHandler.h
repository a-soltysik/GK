#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <functional>

#include "math/Types.h"
#include "Singleton.h"


namespace gk::utils
{

class KeyboardHandler : public Singleton<KeyboardHandler>
{
public:
    using KeyCallback = std::function<void(GLFWwindow*, int, int, int, int)>;
    static auto instance() -> KeyboardHandler&;

    auto addKeyCallback(KeyCallback callback) -> void;

private:
    std::vector<KeyCallback> keyCallbacks;

    friend auto keyCallback(GLFWwindow* window, int key, int scancode, int action ,int mods) -> void;
};

auto keyCallback(GLFWwindow* window, int key, int scancode, int action ,int mods) -> void;



}