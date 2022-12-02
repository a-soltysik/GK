#pragma once

#include <vector>
#include <unordered_map>
#include <optional>
#include <variant>
#include <memory>

#include "Renderable.h"
#include "Light.h"
#include "Camera.h"
#include "handlers/BasicCameraHandler.h"

namespace gk::lab5
{

class Scene
{
public:
    auto startup() -> void;
    auto shutdown() -> void;
    auto render(double time) -> void;

private:
    struct RenderableLight
    {
        uint32_t id;
        gfx::Light light;
        Vector4f color;
        Vector3f multiplier;
        std::unique_ptr<utils::BasicCameraHandler> cameraHandler;
    };

    struct FreeCam
    {
        utils::BasicCameraHandler* currentCameraHandler;
    };

    struct LightCam
    {
        struct Ambient {};
        struct Diffuse {};
        struct Specular {};

        struct Red {};
        struct Green {};
        struct Blue {};

        using State = std::variant<Ambient, Diffuse, Specular, Red, Green, Blue>;

        RenderableLight* currentRenderableLight;

        State state;
    };

    inline static const auto lightStates = std::unordered_map<int, LightCam::State>{
        {GLFW_KEY_COMMA, LightCam::Ambient{}},
        {GLFW_KEY_PERIOD, LightCam::Diffuse{}},
        {GLFW_KEY_SLASH, LightCam::Specular{}},
        {GLFW_KEY_L, LightCam::Red{}},
        {GLFW_KEY_SEMICOLON, LightCam::Green{}},
        {GLFW_KEY_APOSTROPHE, LightCam::Blue{}}
    };


    auto registerCallbacks() -> void;
    auto move(double time) -> void;
    auto moveLight(const utils::Camera& camera) -> void;
    auto setCurrentLight(int key) -> void;
    auto pauseCamHandlers() -> void;
    auto prepareLights() -> void;
    auto renderObjects(double time) -> void;
    auto getCurrentHandler() -> utils::BasicCameraHandler*;
    auto setLightState(int key) -> void;
    auto createLight(Vector3f color, Vector3f multiplier, Vector3f position) -> uint32_t;
    static auto updateLightStates(LightCam& cam, float(*func)(float)) -> void;
    static auto printLightInfo(const RenderableLight& light) -> void;
    static auto drawSphere(const RenderableLight& light) -> void;

    std::unordered_map<uint32_t, RenderableLight> lights;
    std::unique_ptr<utils::BasicCameraHandler> freeCamHandler;
    std::vector<std::unique_ptr<Renderable>> objects;
    std::variant<FreeCam, LightCam> state;
    bool showNormals = false;
    bool isWireframe = false;
};

}
