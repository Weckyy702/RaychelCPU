#include <chrono>
#include <iostream>
#include <thread>

#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"
#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"
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

    scene.setBackgroundTexture({[](const vec3& dir) {
        (void)dir;
        return color{dir} * 0.2F;
    }});

    const Quaternion start_rotation = Quaternion{};
    const vec3 cam_offset = vec3{0, 0, -7};

    auto& cam = scene.setCamera({Transform{cam_offset, start_rotation}, 1.5});

    scene.addObject<SdSphere>(make_object_data({vec3{0, 0, 0}, Quaternion{}}, DiffuseMaterial{color{1, 0, 0}}), 1.0F);
    scene.addObject<SdSphere>(make_object_data({vec3{0.25, -2, 0}, Quaternion{}}, DiffuseMaterial{color{0, 1, 0}}), 1.0F);
    // scene.addObject<SdSphere>(make_object_data({vec3{2.5, 0, 0}, Quaternion{}}, DiffuseMaterial(color(0, 1, 1))), 1.0F);
    // scene.addObject<SdSphere>(make_object_data({vec3{0, 0, -2.5}, Quaternion{}}, DiffuseMaterial(color(0.5, 0, 1))), 1.0F);
    // scene.addObject<SdSphere>(make_object_data({vec3{-2.5, 0, 0}, Quaternion{}}, DiffuseMaterial(color(1))), 1.0F);

    const vec2i size = {640, 360};

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    gsl::owner<RenderTarget*> target = new ImageTargetPng{size, "../../results/res", 4}; // new AsciiTarget{size, true};

    auto label = Logger::startTimer("Total time");

    float a = 0;
    for (size_t i = 0;; i++) {

        auto render_label = Logger::startTimer("Render time");
        auto results = renderer.getImageRendered();
        Logger::logDuration(render_label);

        if (!results) {
            break;
        }

        auto file_label = Logger::startTimer("Write time");
        target->prepareFramebufferWrite();
        target->writeFramebuffer(results.value());
        target->finishFramebufferWrite();
        Logger::logDuration(file_label);

        //cam.update_yaw(2_deg);


        cam.transform_.position = rotateX(rotateZ(rotateY(cam_offset, a * degToRad<>), a * 0.6F * degToRad<>), a * 0.1F * degToRad<>);
        cam.look_at(vec3{});

        a += 1.0F;
    }

    Logger::logDuration(label);

    delete target;

    return 0;
}