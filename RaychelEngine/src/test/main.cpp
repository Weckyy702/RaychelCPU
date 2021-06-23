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

int main(int /*unused*/, char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::log);

    Logger::log("Welcome to Raychel Version ", RAYCHEL_VERSION_TAG, " at ", *argv, '\n');

    Scene scene;

    scene.setBackgroundTexture({[](const vec3& dir) {
        (void)dir;
        return color{dir};
    }});

    Quaternion start_rotation = Quaternion{};

    auto& cam = scene.setCamera({Transform{vec3(0, 0, 0), start_rotation}, 0.75});

    scene.addObject<SdSphere>(make_object_data({vec3{0, 0, 2.5}, Quaternion{}}, DiffuseMaterial{color{1, 0, 0}}), 1.0F);
    scene.addObject<SdSphere>(make_object_data({vec3{2.5, 0, 0}, Quaternion{}}, DiffuseMaterial(color(0, 1, 1))), 1.0F);
    scene.addObject<SdSphere>(make_object_data({vec3{0, 0, -2.5}, Quaternion{}}, DiffuseMaterial(color(0.5, 0, 1))), 1.0F);
    scene.addObject<SdSphere>(make_object_data({vec3{-2.5, 0, 0}, Quaternion{}}, DiffuseMaterial(color(1))), 1.0F);

    const vec2i size = {50, 25};

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    gsl::owner<RenderTarget*> target = new AsciiTarget{size, true}; //new ImageTargetPng{size, "./res", 4}

    auto label = Logger::startTimer("Total time");

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

        cam.update_yaw(2_deg);

        using namespace std::chrono_literals;
    }

    Logger::logDuration(label);

    delete target;

    return 0;
}