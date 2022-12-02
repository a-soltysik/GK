#if defined(_WIN32)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include <GL/glu.h>

#include "Scene.h"
#include "Utils.h"
#include "Egg.h"
#include "math/Math.h"

namespace gk::lab5
{

auto Scene::startup() -> void
{
    registerCallbacks();

    const auto multiplier = Vector3f {0.1f, 0.8f, 1.f};
    const auto red        = Vector3f {1.f, .0f, .0f};
    createLight(red, multiplier, {0.f, 0.f, 10.f});

    const auto green = Vector3f {0.5f, 1.f, 0.f};
    createLight(green, multiplier, {10.f, 10.f, 0.f});

    const auto cyan = Vector3f {.0f, 1.f, 1.f};
    createLight(cyan, multiplier, {0.f, 0.f, -10.f});

    const auto purple = Vector3f {0.5f, 0.f, 1.f};
    createLight(purple, multiplier, {-10.f, -10.f, -10.f});

    freeCamHandler = std::make_unique<utils::BasicCameraHandler>(
        utils::Camera {
            {-10.f, 0.f, 0.f},
            {0.f,   1.f, 0.f},
            {10.f,  0.f, 0.f}
        }
    );

    state = FreeCam {freeCamHandler.get()};

    objects.push_back(std::make_unique<Egg>(Egg {50}));
}

auto Scene::registerCallbacks() -> void
{
    utils::KeyboardHandler::instance().addKeyCallback([this](auto*, auto key, auto, auto action, auto) {
        if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
        {
            showNormals = !showNormals;
        }
        if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        {
            isWireframe = !isWireframe;
        }
        if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        {
            state = FreeCam {
                freeCamHandler.get()
            };
            pauseCamHandlers();
            freeCamHandler->start();
        }
        if (action == GLFW_PRESS)
        {
            setCurrentLight(key);
            setLightState(key);
        }
        if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            std::visit(utils::match {
                [](LightCam& lightCam) {
                    updateLightStates(lightCam, [](float factor) {
                        return factor + 0.1f;
                    });
                    printLightInfo(*lightCam.currentRenderableLight);
                },
                [](auto) { }
            }, state);
        }
        if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            std::visit(utils::match {
                [](LightCam& lightCam) {
                    updateLightStates(lightCam, [](float factor) {
                        return factor - 0.1f;
                    });
                    printLightInfo(*lightCam.currentRenderableLight);
                },
                [](auto) { }
            }, state);
        }
    });
}

auto Scene::render(double time) -> void
{
    if (isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    move(time);
    prepareLights();
    renderObjects(time);
}

auto Scene::move(double time) -> void
{
    const auto camera = getCurrentHandler()->getCameraState(time);
    const auto center = vec::add(camera.position, camera.direction);

    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
              center.x, center.y, center.z,
              camera.up.x, camera.up.y, camera.up.z);

    moveLight(camera);
}

auto Scene::pauseCamHandlers() -> void
{
    freeCamHandler->pause();
    for (auto& light : lights)
    {
        light.second.cameraHandler->pause();
    }
}

auto Scene::drawSphere(const RenderableLight& light) -> void
{
    auto* quadratic = gluNewQuadric();
    glPushMatrix();
    glTranslatef(light.light.position.x, light.light.position.y, light.light.position.z);
    gfx::makeMaterial(vec::vec3from(light.color), {1.f, 1.f, 1.f}, 1.f).prepareMaterial();
    gluSphere(quadratic, 1, 100, 20);
    gluDeleteQuadric(quadratic);
    glPopMatrix();
}

auto Scene::prepareLights() -> void
{
    for (auto& pair : lights)
    {
        pair.second.light.ambient  = vec::multiply(pair.second.color, pair.second.multiplier.x);
        pair.second.light.diffuse  = vec::multiply(pair.second.color, pair.second.multiplier.y);
        pair.second.light.specular = vec::multiply(pair.second.color, pair.second.multiplier.z);
        pair.second.light.enable(pair.first);

        std::visit(utils::match {
            [&pair](const LightCam& lightCam) {
                if (lightCam.currentRenderableLight->id != pair.first)
                {
                    drawSphere(pair.second);
                }
            },
            [&pair](const FreeCam&) {
                drawSphere(pair.second);
            }
        }, state);
    }
}

auto Scene::renderObjects(double time) -> void
{
    utils::axes(6, 6, 6);

    for (const auto& object : objects)
    {
        object->render(time);
        if (showNormals)
        {
            object->renderNormals();
        }
    }
}

auto Scene::getCurrentHandler() -> utils::BasicCameraHandler*
{
    return std::visit(utils::match {
        [](LightCam& lightCam) {
            return lightCam.currentRenderableLight->cameraHandler.get();
        },
        [](FreeCam& freeCam) {
            return freeCam.currentCameraHandler;
        }
    }, state);
}

auto Scene::moveLight(const utils::Camera& camera) -> void
{
    std::visit(utils::match {
        [&camera](LightCam& lightCam) {
            lightCam.currentRenderableLight->light.position = vec::vec4from(camera.position);
        },
        [](const auto&) {
        }
    }, state);
}

auto Scene::setCurrentLight(int key) -> void
{
    const auto symbol = utils::KeyboardHandler::instance().keys[key];
    if (symbol >= '1' && symbol <= '8')
    {
        const auto it = lights.find(static_cast<uint32_t>(symbol - '0' - 1));
        if (it != lights.cend())
        {
            state = LightCam {
                &it->second,
                LightCam::Ambient {}
            };
            pauseCamHandlers();
            it->second.cameraHandler->start();
        }
    }
}

auto Scene::setLightState(int key) -> void
{
    auto it = lightStates.find(key);
    if (it != lightStates.cend())
    {
        std::visit(utils::match {
            [it](LightCam& lightCam) {
                lightCam.state = it->second;
            },
            [](auto) { }
        }, state);
    }
}

auto Scene::printLightInfo(const RenderableLight& light) -> void
{
    std::cout << "Color: R: " << light.color.x
              << " G: " << light.color.y
              << " B: " << light.color.z
              << "\n";

    std::cout << "Light: Ambient: " << light.multiplier.x
              << " Diffuse: " << light.multiplier.y
              << " Specular: " << light.multiplier.z
              << "\n";
}

auto Scene::createLight(Vector3f color, Vector3f multiplier, Vector3f position) -> uint32_t
{
    static auto id    = uint32_t {};
    const auto  light = lights.insert({id, RenderableLight {
        .id = id,
        .light = {
            .ambient = vec::vec4from(vec::multiply(color, multiplier.x)),
            .diffuse = vec::vec4from(vec::multiply(color, multiplier.y)),
            .specular = vec::vec4from(vec::multiply(color, multiplier.z)),
            .position = vec::vec4from(position),
            .attenuation = {
                1.f, 0.05f, 0.001f
            },
        },
        .color = vec::vec4from(color),
        .multiplier = multiplier,
        .cameraHandler = std::make_unique<utils::BasicCameraHandler>(
            utils::Camera {
                position,
                {0.f, 1.f, 0.f},
                vec::multiply(position, -1.f)
            }
        ),
    }});
    if (light.second)
    {
        light.first->second.cameraHandler->pause();
        return id++;
    }
    return std::numeric_limits<uint32_t>::max();
}

auto Scene::shutdown() -> void
{

}

auto Scene::updateLightStates(LightCam& cam, float (* func)(float)) -> void
{
    std::visit(utils::match {
        [&cam, func](LightCam::Ambient) {
            cam.currentRenderableLight->multiplier.x = func(cam.currentRenderableLight->multiplier.x);
            cam.currentRenderableLight->multiplier.x = std::clamp(
                cam.currentRenderableLight->multiplier.x, 0.f, 1.f);
        },
        [&cam, func](LightCam::Diffuse) {
            cam.currentRenderableLight->multiplier.y = func(cam.currentRenderableLight->multiplier.y);
            cam.currentRenderableLight->multiplier.y = std::clamp(
                cam.currentRenderableLight->multiplier.y, 0.f, 1.f);
        },
        [&cam, func](LightCam::Specular) {
            cam.currentRenderableLight->multiplier.z = func(cam.currentRenderableLight->multiplier.z);
            cam.currentRenderableLight->multiplier.z = std::clamp(
                cam.currentRenderableLight->multiplier.z, 0.f, 1.f);
        },
        [&cam, func](LightCam::Red) {
            cam.currentRenderableLight->color.x = func(cam.currentRenderableLight->color.x);
            cam.currentRenderableLight->color.x = std::clamp(
                cam.currentRenderableLight->color.x, 0.f, 1.f);
        },
        [&cam, func](LightCam::Green) {
            cam.currentRenderableLight->color.y = func(cam.currentRenderableLight->color.y);
            cam.currentRenderableLight->color.y = std::clamp(
                cam.currentRenderableLight->color.y, 0.f, 1.f);
        },
        [&cam, func](LightCam::Blue) {
            cam.currentRenderableLight->color.z = func(cam.currentRenderableLight->color.z);
            cam.currentRenderableLight->color.z = std::clamp(
                cam.currentRenderableLight->color.z, 0.f, 1.f);
        },
    }, cam.state);
}

}