#include "KeyboardHandler.h"

namespace gk::utils
{

auto KeyboardHandler::addKeyCallback(const gk::utils::KeyboardHandler::KeyCallback& callback) -> void
{
    keyCallbacks.push_back(callback);
}

auto keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
{
    for (const auto& callback : KeyboardHandler::instance().keyCallbacks)
    {
        callback(window, key, scancode, action, mods);
    }
}

auto KeyboardHandler::instance() -> KeyboardHandler&
{
    static auto handler = KeyboardHandler{};
    return handler;
}


}

