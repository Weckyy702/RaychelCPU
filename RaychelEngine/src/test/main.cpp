#include <iostream>

#include <png++/png.hpp>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"

using namespace Raychel;

int main(int argc, char** argv)
{
    Logger::setMinimumLogLevel(Logger::LogLevel::debug);

    Scene scene;

    scene.addObject( SdSphere{ ObjectData{Transform{}} , 1.0 } );

    RenderController renderer;

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize({1000, 1000});

    auto results = renderer.getImageRendered();

    png::image<png::rgb_pixel_16> image{1000, 1000};

    for(auto y = 0; y < image.get_height(); y++) {
        for(auto x = 0; x < image.get_width(); x++) {
            auto idx = y * image.get_width() + x;
            //RAYCHEL_LOG(results.at(idx).output);
            auto col = color{results.at(idx).output}.to<uint16_t>();
            //RAYCHEL_LOG("Saving color ", col);
            image.set_pixel(x, y, png::rgb_pixel_16{col.r, col.g, col.b});

        }
    }

    image.write("res_16.png");

    return 0;
}