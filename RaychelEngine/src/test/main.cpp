#include <chrono>
#include <iostream>
#include <thread>

#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Lights/lamps.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"
#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"
#include "Raychel/Engine/Rendering/RenderTarget/NullTarget.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Raychel.h"
#include "Raychel/Core/RaychelMath/vector.h"
#include "Raychel/Core/RaychelMath/Impl/vectorImpl.inl"

#include "Raychel/Engine/Materials/Materials.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

using namespace Raychel;

int main(int /*unused*/, const char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::log);
    Logger::setOutStream(std::cerr);

    Logger::log("Welcome to Raychel Version ", RAYCHEL_VERSION_TAG, " at ", *argv, '\n');
    Scene scene;

    scene.set_background_texture({color{0}});

    const Quaternion start_rotation{};
    const vec3 cam_offset = vec3{0, 0, -7};

    auto& cam = scene.set_camera({Transform{cam_offset, start_rotation}, 1.5});

    scene.add_object<SdSphere>(make_object_data({vec3{0, 0, 0}, Quaternion{}}, DiffuseMaterial{color{1}}), 1.0F);
    // scene.add_object<SdSphere>(make_object_data({normalize(vec3{1, 2, -1}), Quaternion{}}, DiffuseMaterial{color{1}}), .375F);
    // scene.add_object<SdSphere>(make_object_data({normalize(vec3{-1, 2, -1}), Quaternion{}}, DiffuseMaterial{color{1}}), .375F);
    scene.add_object<SdPlane>(make_object_data({}, DiffuseMaterial{color{1}}), vec3{0, 1, 0}, -1.0F);

    scene.add_lamp<DirectionalLight>(LampData{color{1, 0, 0}, 0.75F, 0.0F}, vec3{0, -1, 1});
    scene.add_lamp<DirectionalLight>(LampData{color{0, 1, 0}, 0.875F, 0.0F}, vec3{-1, -1, 1});
    auto& blue_lamp = scene.add_lamp<DirectionalLight>(LampData{color{0, 0, 1}, 1.0F, 0.0F}, vec3{1, -1, 1});
    //scene.add_lamp<DirectionalLight>(LampData{color{1}, 1.0F, 0.0F}, vec3{0, 1, 0});

    const vec2i size = vec2i{3840, 2160} / 4UL;

    RenderController& renderer = scene.get_renderer();

    //renderer.set_render_settings({/*TODO: RenderSettings*/});

    renderer.set_output_size(size);

    // new AsciiTarget{size, true, " .:-=+*#%@"}; // new NullTarget{size};
    gsl::owner<RenderTarget*> target = new ImageTargetPng{size, "../../results/res", 4};

    auto label = Logger::startTimer("Total time");

    float a = 0;
    for (size_t i = 0; i < 360; i++) {

        cam.look_at(vec3{});

        auto render_label = Logger::startTimer("Render time");
        auto results = renderer.get_rendered_image();
        Logger::logDuration(render_label);

        if (!results) {
            break;
        }

        auto file_label = Logger::startTimer("Write time");
        target->prepareFramebufferWrite();
        target->writeFramebuffer(results.value());
        target->finishFramebufferWrite();
        Logger::logDuration(file_label);

        blue_lamp.direction_ = rotateX(normalize(vec3{1, -1, 1}), a*0.25F);
        //cam.transform_.position = rotateY(cam_offset, a);
        //cam.transform_.position.y = 2.0F * std::sin(a * 2.0F);

        a += 1.0F / 30.0F;
    }

    Logger::logDuration(label);

    delete target;

    return 0;
}
