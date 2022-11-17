#include <cstdlib>

#include "Utils.h"

namespace gk::utils
{

static auto gBounds    = Vector2f {};
static auto gNearDepth = 100.f;
static auto gFarDepth  = 100.f;

auto configureViewport(Vector2f bounds, float nearDepth, float farDepth) -> void
{
    gBounds    = bounds;
    gNearDepth = nearDepth;
    gFarDepth  = farDepth;
}

auto viewport([[maybe_unused]] GLFWwindow* window, int width, int height) -> void
{
    if (height == 0)
    {
        height = 1;
    }
    if (width == 0)
    {
        width = 1;
    }

    const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, width, height);
    glLoadIdentity();

    if (width <= height)
    {
        glOrtho(-gBounds.x, gBounds.x, -gBounds.y / aspectRatio, gBounds.y / aspectRatio, gNearDepth, gFarDepth);
    }
    else
    {
        glOrtho(-gBounds.x * aspectRatio, gBounds.x * aspectRatio, -gBounds.y, gBounds.y, gNearDepth, gFarDepth);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

auto makeWindow(Vector2i dimensions, bool vsync) -> GLFWwindow*
{
    if (!glfwInit())
    {
        std::exit(-1);
    }

    auto* window = glfwCreateWindow(static_cast<int>(dimensions.x), static_cast<int>(dimensions.y), __FILE__, nullptr,
                                    nullptr);
    if (!window)
    {
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, viewport);
    glfwSwapInterval(vsync ? 1 : 0);

    return window;
}

auto axes(float x, float y, float z) -> void
{
    glBegin(GL_LINES);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-x, 0.f, 0.0);
    glVertex3f(x, 0.f, 0.f);

    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, -y, 0.f);
    glVertex3f(0.f, y, 0.f);

    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.f, -z);
    glVertex3f(0.f, 0.f, z);
    glEnd();
}

auto spin(float angle) -> void
{
    glRotatef(angle, 1.f, 0.f, 0.f);
    glRotatef(angle, 0.f, 1.f, 0.f);
    glRotatef(angle, 0.f, 0.f, 1.f);
}
}
