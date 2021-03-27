#include <iostream>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"

using namespace Raychel;

int main(int argc, char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::debug);

    Scene scene;

    Quaternion start_rotation = Quaternion{ vec3{0, 0, -1}, 45_deg };

    scene.cam = Camera{Transform{vec3(0, 0, 0), start_rotation}, 0.5};

    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, 7.5}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, -7.5, 0}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, -7.5}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 7.5, 0}}}, 1.0 } );

    const vec2Imp<size_t> size = {1280, 720};

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    ImageTarget target{size, "../../res", 4};

    auto label = Logger::startTimer("Total time");

    for(int i = 0; i < 360; i++) {

        auto render_label = Logger::startTimer("Render time");
        auto results = renderer.getImageRendered();
        Logger::logDuration(render_label);

        target.writeFramebuffer(results);

        scene.cam.updatePitch(1_deg);
    }

    Logger::logDuration(label);

    return 0;
}