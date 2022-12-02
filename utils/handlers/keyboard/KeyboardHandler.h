#pragma once

#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GLFW/glfw3.h>

#include <unordered_map>
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

    std::unordered_map<int, char> keys = {
        {GLFW_KEY_0, '0'},
        {GLFW_KEY_1, '1'},
        {GLFW_KEY_2, '2'},
        {GLFW_KEY_3, '3'},
        {GLFW_KEY_4, '4'},
        {GLFW_KEY_5, '5'},
        {GLFW_KEY_6, '6'},
        {GLFW_KEY_7, '7'},
        {GLFW_KEY_8, '8'},
        {GLFW_KEY_9, '9'},
    };

private:
    std::vector<KeyCallback> keyCallbacks;

    friend auto keyCallback(GLFWwindow* window, int key, int scancode, int action ,int mods) -> void;
};

auto keyCallback(GLFWwindow* window, int key, int scancode, int action ,int mods) -> void;



}