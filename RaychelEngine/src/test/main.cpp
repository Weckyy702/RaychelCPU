#include <iostream>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"

using namespace Raychel;

int main(int argc, char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::debug);
    Logger::log("Hello, World!\n");

    Scene scene;

    scene.addObject( SdSphere{ObjectData{Transform{}}, 1.0} );

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize({4, 4});

    auto results = renderer.getRenderedImage();

    for(const auto& res : results) {
        Logger::debug(res.output, '\n');
    }

    return 0;
}