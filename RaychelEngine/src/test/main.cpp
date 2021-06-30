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

#include "Raychel/Engine/Materials/Materials.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

using namespace Raychel;

int main(int /*unused*/, const char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::log);
    Logger::setOutStream(std::cerr);

    Logger::log("Welcome to Raychel Version ", RAYCHEL_VERSION_TAG, " at ", *argv, '\n');

    Scene scene;

    scene.set_background_texture({[](const vec3& dir) {
        (void)dir;
        return color{0.05F};
    }});

    const Quaternion start_rotation = Quaternion{};
    const vec3 cam_offset = vec3{0, 0, 7};

    auto& cam = scene.set_camera({Transform{cam_offset, start_rotation}, 1.5});

    scene.add_object<SdSphere>(make_object_data({vec3{0, 0, 0}, Quaternion{}}, DiffuseMaterial{color{1}}), 1.0F);
    scene.add_object<SdPlane>(make_object_data({}, DiffuseMaterial{color{1}}), vec3{0, 1, 0}, -1.0F);

    scene.add_lamp<DirectionalLight>(LampData{color{1, 0, 0}, 0.75F, 0.0F}, vec3{0, -1, 1});
    scene.add_lamp<DirectionalLight>(LampData{color{0, 1, 0}, 0.875F, 0.0F}, vec3{-1, -1, 1});
    scene.add_lamp<DirectionalLight>(LampData{color{0, 0, 1}, 1.0F, 0.0F}, vec3{1, -1, 1});
    scene.add_lamp<DirectionalLight>(LampData{color{1}, 1.0F, 0.0F}, vec3{0, 1, 0});

    const vec2i size = vec2i{50, 25};//vec2i{3840, 2160} / 2UL;

    RenderController& renderer = scene.get_renderer();

    //renderer.set_render_settings({/*TODO: RenderSettings*/});

    renderer.set_output_size(size);

    //new ImageTargetPng{size, "../../results/res", 4}; // new NullTarget{size};
    gsl::owner<RenderTarget*> target = new AsciiTarget{size, true};

    auto label = Logger::startTimer("Total time");

    float a = 0;
    for (size_t i = 0;; i++) {

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

        cam.transform_.position = rotateX(cam_offset, a);
        //cam.transform_.position.y = 2.0F * std::sin(a * 0.5F);
        cam.look_at(vec3{});

        a += 1.0F / 30.0F;
    }

    Logger::logDuration(label);

    delete target;
    return 0;
}
