#include <iostream>
#include <thread>
#include <chrono>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"
#include "Raychel/Engine/Rendering/RenderTarget/AsciiTarget.h"

using namespace Raychel;

struct DebugMat : public Material {

    DebugMat()=default;

    DebugMat(const color& col)
        :col_{col}
    {}

    void initializeTextureProviders(const vec3&, const vec3&){}

    color getSurfaceColor(const ShadingData& data, size_t recursion_depth) const override {
        const vec3 out_direction = reflect(data.in_direction, data.hit_normal);
        if(recursion_depth == 3) {
            return color{1};
        }
        return parent_renderer_->getShadedColor(data.surface_point, out_direction, recursion_depth)*0.95f;//return col_ * std::max(0.0f, dot(data.hit_normal, vec3{0, -1, 0}));
    }

    const color col_;
};

int main(int, char**)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::error);

    Logger::log("Welcome to Raychel Version ", RAYCHEL_VERSION_TAG, '\n');

    Scene scene;

    Quaternion start_rotation = Quaternion{};

    scene.cam = Camera{Transform{vec3(0, 0, 0), start_rotation}, 0.5};

    scene.addObject( make_object<SdSphere>(Transform{vec3{0, 0, 2.5}}, DebugMat{color{1, 0, 0}}, 1.0) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{0, -2.5, 0}}, DebugMat{color{0, 1, 0}}, 1.0) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{0, 0, -2.5}}, DebugMat{color{0, 0, 1}}, 1.0) );
    scene.addObject( make_object<SdSphere>(Transform{vec3{0, 2.5, 0}}, DebugMat{color{1, 1, 0}}, 1.0) );

    const vec2i size = {100, 50};

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    RenderTarget* target = new AsciiTarget{size};//ImageTargetPng{size, "../../res", 4};

    auto label = Logger::startTimer("Total time");

    for(size_t i = 0;; i++) {
        //auto render_label = Logger::startTimer("Render time");
        auto results = renderer.getImageRendered();
        //Logger::logDuration(render_label);

        if(!results) {
            break;
        }
        
        target->prepareFramebufferWrite();
        //auto file_label = Logger::startTimer("Write time");
        target->writeFramebuffer(results.value());
        //Logger::logDuration(file_label);
        target->finishFramebufferWrite();

        scene.cam.updateYaw(1_deg);
    }

    Logger::logDuration(label);

    delete target;

    return 0;
}