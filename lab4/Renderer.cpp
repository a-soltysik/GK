#include <GL/glu.h>

#include "Renderer.h"
#include "Config.h"
#include "math/Math.h"
#include "Handlers/Mouse/SceneRotationMouseHandler.h"

namespace gk::lab4
{

auto Renderer::run(Vector2i dimensions, bool vsync) -> void
{
    this->dimensions = dimensions;
    utils::KeyboardHandler::instance().addKeyCallback([this](auto, auto button, auto, auto action, auto) {
        if (button == GLFW_KEY_ENTER && action == GLFW_PRESS)
        {
            freeRoam = !freeRoam;
        }
    });

    utils::configureViewport(bounds, nearDepth, farDepth);
    utils::defaultInit(dimensions,
                       [this] { startup(); },
                       [this](auto time) { render(time); },
                       [this] { shutdown(); },
                       utils::Config::Dimensions::_3D,
                       vsync);
}

auto Renderer::setObject(std::unique_ptr<Renderable> newObject) -> void
{
    object = std::move(newObject);
}

auto Renderer::startup() const -> void
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
    utils::viewport(nullptr, dimensions.x, dimensions.y);
}

auto Renderer::shutdown() -> void
{

}

auto Renderer::render(double time) -> void
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (freeRoam)
    {
        freeMove(time);
    }
    else
    {
        moveAround();
    }

    utils::axes(6, 6, 6);

    object->render(time);

    glFlush();
}

auto Renderer::freeMove(double time) -> void
{
    static constexpr auto up = Vector3f {0.f, 1.f, 0.f};

    const auto cameraFront = getCameraDirection();
    const auto cameraRight = vec::normalized(vec::cross(up, cameraFront));
    const auto cameraUp    = vec::cross(cameraFront, cameraRight);

    const auto velocity    = getVelocity(cameraFront, cameraUp);
    const auto translation = vec::multiply(velocity, static_cast<float>(time));
    camera = vec::add(camera, translation);

    const auto center = vec::add(camera, cameraFront);

    gluLookAt(camera.x, camera.y, camera.z,
              center.x, center.y, center.z,
              cameraUp.x, cameraUp.y, cameraUp.z);
}

auto Renderer::moveAround() -> void
{
    rotateAroundManually();
}

auto Renderer::getCameraDirection() -> Vector3f
{
    static auto rotationHandler = utils::SceneRotationMouseHandler {{-90., std::numeric_limits<double>::lowest()},
                                                                    {90.,  std::numeric_limits<double>::max()}};

    const auto angleX = rotationHandler.getSceneRotationInDegrees().x;
    const auto angleY = rotationHandler.getSceneRotationInDegrees().y;

    const auto cosX = static_cast<float>(std::cos(utils::toRadians(angleX)));
    const auto cosY = static_cast<float>(std::cos(utils::toRadians(angleY)));
    const auto sinX = static_cast<float>(std::sin(utils::toRadians(angleX)));
    const auto sinY = static_cast<float>(std::sin(utils::toRadians(angleY)));

    return vec::normalized(Vector3f {
        sinY * cosX,
        -sinX,
        -cosY * cosX,
    });
}

auto Renderer::getVelocity(Vector3f cameraFront, Vector3f cameraUp) -> Vector3f
{
    const auto moveDirection = movementHandler.getSceneMovement();

    auto move = Vector3f {};
    if (moveDirection.z != 0.f)
    {
        move = vec::add(move, vec::multiply(cameraFront, moveDirection.z));
    }
    if (moveDirection.x != 0.f)
    {
        move = vec::add(move, vec::cross(vec::multiply(cameraFront, moveDirection.x), cameraUp));
    }
    if (moveDirection.y != 0.f)
    {
        move.y = moveDirection.y;
    }

    const auto velocity = utils::Config::instance().velocity;
    return {
        move.x * velocity.x,
        move.y * velocity.y,
        move.z * velocity.z
    };
}

auto Renderer::rotateAroundGlStyle() -> void
{
    static auto rotationHandler = utils::SceneRotationMouseHandler {
        {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
        {std::numeric_limits<double>::max(),    std::numeric_limits<double>::max()}
    };

    static constexpr auto maxScaleFactor = 1.5;

    const auto scaleFactor = static_cast<float>(std::min(maxScaleFactor, scaleHandler.getSceneScale()));

    const auto angleX = rotationHandler.getSceneRotationInDegrees().x;
    const auto angleY = rotationHandler.getSceneRotationInDegrees().y;

    gluLookAt(camera.x, camera.y, camera.z, 0., 0., 0., 0., 1., 0.);

    glRotated(angleX, 1.0, 0.0, 0.0);
    glRotated(angleY, 0.0, 1.0, 0.0);
    glScaled(scaleFactor, scaleFactor, scaleFactor);
}

auto Renderer::rotateAroundManually() -> void
{
    constexpr static auto center = Vector3f {0, 0, 0};

    const auto position = getCameraPosition(center);

    gluLookAt(position.first.x, position.first.y, position.first.z,
              center.x, center.y, center.z,
              position.second.x, position.second.y, position.second.z);
}

auto Renderer::getCameraPosition(Vector3f center) -> std::pair<Vector3f, Vector3f>
{
    static auto rotationHandler = utils::SceneRotationMouseHandler {
        {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()},
        {std::numeric_limits<double>::max(),    std::numeric_limits<double>::max()}
    };

    static constexpr auto maxScaleFactor = 1.5;

    const auto scaleFactor = static_cast<float>(std::min(maxScaleFactor, scaleHandler.getSceneScale()));

    const auto angleX = rotationHandler.getSceneRotationInDegrees().x;
    const auto angleY = rotationHandler.getSceneRotationInDegrees().y;

    const auto cosX = static_cast<float>(std::cos(utils::toRadians(angleX)));
    const auto cosY = static_cast<float>(std::cos(utils::toRadians(angleY)));
    const auto sinX = static_cast<float>(std::sin(utils::toRadians(angleX)));
    const auto sinY = static_cast<float>(std::sin(utils::toRadians(angleY)));

    const auto distance = vec::distance(camera, center);

    return {vec::add({-distance * sinY * cosX / scaleFactor,
                      distance * sinX / scaleFactor,
                      distance * cosY * cosX / scaleFactor},
                     center),
            {0.f, cosX >= 0.f ? 1.f : -1.f, 0.f}};
}

}
