#include "BasicCameraHandler.h"
#include "math/Math.h"
#include "Config.h"

namespace gk::utils
{

BasicCameraHandler::BasicCameraHandler(const Camera& camera)
    : camera {camera}
    , angleOffset {calculateOffset(camera)}
    , rotationHandler {{-90. - angleOffset.x, std::numeric_limits<double>::lowest()},
                       {90. - angleOffset.x,  std::numeric_limits<double>::max()}}
{

}

auto BasicCameraHandler::getCameraState(double time) -> Camera
{
    if (!isPaused)
    {
        camera.direction = getCameraDirection();
        const auto cameraRight = vec::normalized(vec::cross(vec::UP<float>, camera.direction));
        camera.up = vec::cross(camera.direction, cameraRight);

        const auto velocity    = getVelocity();
        const auto translation = vec::multiply(velocity, static_cast<float>(time));
        camera.position = vec::add(camera.position, translation);
    }

    return camera;
}

auto BasicCameraHandler::getCameraDirection() -> Vector3f
{
    const auto angleX = rotationHandler.getSceneRotationInDegrees().x + angleOffset.x;
    const auto angleY = rotationHandler.getSceneRotationInDegrees().y + angleOffset.y;

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

auto BasicCameraHandler::getVelocity() const -> Vector3f
{
    const auto moveDirection = utils::SceneMovementHandler::instance().getSceneMovement();

    auto move = Vector3f {};
    if (moveDirection.z != 0.f)
    {
        move = vec::add(move, vec::multiply(camera.direction, moveDirection.z));
    }
    if (moveDirection.x != 0.f)
    {
        move = vec::add(move, vec::cross(vec::multiply(camera.direction, moveDirection.x), camera.up));
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

auto BasicCameraHandler::pause() -> void
{
    isPaused = true;
    rotationHandler.pause();
}

auto BasicCameraHandler::start() -> void
{
    isPaused = false;
    rotationHandler.start();
}

auto BasicCameraHandler::calculateOffset(const Camera& camera) -> Vector2f
{
    return {static_cast<float>(-utils::toDegrees(
        std::atan2(camera.direction.y,
                   std::sqrt(camera.direction.x * camera.direction.x + camera.direction.z * camera.direction.z)))),
            static_cast<float>(utils::toDegrees(std::atan2(camera.direction.x, -camera.direction.z)))};
}

}

