#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GL/glu.h>

#include "Renderer.h"
#include "Config.h"
#include "math/Math.h"
#include "Utils.h"

namespace gk::lab6
{

auto Renderer::run(Vector2i dimensions, bool vsync) -> void
{
    this->dimensions = dimensions;

    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       utils::Config::Dimensions::_3D,
                       vsync);
}

auto Renderer::setScene(std::unique_ptr<Scene> newScene) -> void
{
    scene = std::move(newScene);
}

auto Renderer::startup() -> void
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);


    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    scene->startup();
}

auto Renderer::shutdown() -> void
{
    scene->shutdown();
}

auto Renderer::render(double time) -> void
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glLoadIdentity();

    scene->render(time);

    glFlush();
}

}
