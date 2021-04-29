#include <iostream>
#include <thread>
#include <chrono>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"
#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

#include "Raychel/Engine/Materials/Materials.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

using namespace Raychel;

int main(int, char**)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::debug);

    Logger::log("Welcome to Raychel Version ", RAYCHEL_VERSION_TAG, '\n');

    Scene scene;

    scene.background_texture_ = CubeTexture<color>{[](const vec3& dir){
        return color{dir};
    }};

    Quaternion start_rotation = Quaternion{};

    scene.cam = Camera{Transform{vec3(0, 0, 0), start_rotation}, 1.0};

    scene.addObject( make_object<SdSphere>(Transform{vec3{0, 0, 2.5}}, DiffuseMaterial{color{1, 0, 0}}, 1.0f) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{2.5, 0, 0}}, DiffuseMaterial{color{0, 1, 0}}, 1.0f) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{0, 0, -2.5}}, DiffuseMaterial{color{0, 0, 1}}, 1.0f) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{-2.5, 0, 0}}, DiffuseMaterial{color{1, 1, 1}}, 1.0f) );

    const vec2i size = {853, 480};

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    RenderTarget* target = new ImageTargetPng{size, "../../res", 4};

    auto label = Logger::startTimer("Total time");

    for(size_t i = 0;i<180; i++) {

        auto render_label = Logger::startTimer("Render time");
        auto results = renderer.getImageRendered();
        Logger::logDuration(render_label);

        if(!results) {
            break;
        }
        
        auto file_label = Logger::startTimer("Write time");
            target->prepareFramebufferWrite();
            target->writeFramebuffer(results.value());
            target->finishFramebufferWrite();
        Logger::logDuration(file_label);

        scene.cam.updateYaw(2_deg);

        using namespace std::chrono_literals;
    }

    Logger::logDuration(label);

    delete target;

    return 0;
}