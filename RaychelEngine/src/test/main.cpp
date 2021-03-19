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

    const vec2i size = {1080, 1920};

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size);

    auto results = renderer.getImageRendered();

    using rgb_t = png::byte;
    using pixel_t = png::basic_rgb_pixel<rgb_t>;

    png::image<pixel_t, png::solid_pixel_buffer<pixel_t>> image{size.x, size.y};

    for(auto y = 0; y < image.get_height(); y++) {
        for(auto x = 0; x < image.get_width(); x++) {
            auto idx = y * image.get_width() + x;
            auto col = color{results.at(idx).output}.to<rgb_t>();
            image.set_pixel(x, y, pixel_t{col.r, col.g, col.b});

        }
    }

    if(size.x > size.y)
        image.write("../../res_wide.png");
    else 
        image.write("../../res_tall.png");

    return 0;
}