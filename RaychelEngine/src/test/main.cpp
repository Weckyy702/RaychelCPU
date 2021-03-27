#include <iostream>
#include <iomanip>
#include <execution>
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

    Quaternion start_rotation = Quaternion{ vec3{0, 0, -1}, 45_deg };

    scene.cam = Camera{Transform{vec3(0, 0, 0), start_rotation}, 0.5};

    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, 7.5}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, -7.5, 0}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 0, -7.5}}}, 1.0 } );
    scene.addObject( SdSphere{ ObjectData{Transform{vec3{0, 7.5, 0}}}, 1.0 } );

    RenderController renderer;

    const vec2Imp<png::uint_32> size = {1280, 720};

    const vec2 _size = size.to<double>() - vec2{1, 1};

    renderer.setCurrentScene(&scene);
    renderer.setOutputSize(size.to<size_t>());

    auto label = Logger::startTimer("Total time");

    for(int i = 0; i < 10; i++) {

        auto render_label = Logger::startTimer("Render time");
        auto results = renderer.getImageRendered();
        Logger::logDuration(render_label);

        using rgb_t = png::uint_16;
        using pixel_t = png::basic_rgb_pixel<rgb_t>;

        png::image<pixel_t, png::solid_pixel_buffer<pixel_t>> image{size.x, size.y};

        std::for_each(results.begin(), results.end(), [&](const RenderResult& res) {
            const auto screen_uv = res.uv * _size;
            const auto pixel_uv = screen_uv.to<png::uint_32>();

            const auto col = res.output.to<rgb_t>();

            image.set_pixel(pixel_uv.x, pixel_uv.y, pixel_t{col.r, col.g, col.b});
        });

        std::ostringstream os;
        os << "../../res_" << std::setw(3) << std::setfill('0') << i << ".png";

        image.write(os.str());

        RAYCHEL_LOG("Finished writing image!");

        scene.cam.updatePitch(36_deg);
    }

    Logger::logDuration(label);

    return 0;
}