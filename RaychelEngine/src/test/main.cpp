#include <iostream>
#include <iomanip>
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

    scene.cam = Camera{Transform{vec3(0, 0, 0)}, 1.0};

    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, 7.5}}} , 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, -7.5, 0}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, -7.5}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 7.5, 0}}}, 1.0 } );

    RenderController renderer;

    const vec2Imp<png::uint_32> size = {1280, 720};

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size.to<size_t>());

    for(int i = 0; i < 360; i++) {

        auto results = renderer.getImageRendered();

        using rgb_t = png::uint_16;
        using pixel_t = png::basic_rgb_pixel<rgb_t>;

        png::image<pixel_t, png::solid_pixel_buffer<pixel_t>> image{size.x, size.y};

        for(auto y = 0u; y < image.get_height(); y++) {
            for(auto x = 0u; x < image.get_width(); x++) {
                const auto idx = y * image.get_width() + x;
                const auto col = results.at(idx).output.to<rgb_t>();
                image.set_pixel(x, y, pixel_t{col.r, col.g, col.b});
            }
        }

        std::ostringstream os;
        os << "../../res_" << std::setw(4) << std::setfill('0') << i << ".png";

        image.write(os.str());

        RAYCHEL_LOG("Finished writing image!");

        scene.cam.transform_.rotation *= Quaternion{ scene.cam.up(), 1_deg };
    }

    return 0;
}