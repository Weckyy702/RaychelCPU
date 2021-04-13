#include "Raychel/Engine/Rendering/RenderTarget/ImageTarget.h"

#include <sstream>
#include <iomanip>

#include <png++/png.hpp>

namespace Raychel
{
        using rgb_t = png::uint_16;
        using pixel_t = png::basic_rgb_pixel<rgb_t>;
        using image_t = png::image<pixel_t, png::solid_pixel_buffer<pixel_t>>;

    void ImageTargetPng::writeFramebuffer(const Texture<RenderResult>& framebuffer)
    {

        RAYCHEL_LOG("Writing framebuffer to image...")

        //RAYCHEL_ASSERT(framebuffer.size() == getSize());

        const auto image_size = size().to<png::uint_32>();
        const auto _size = image_size.to<float>() - vec2{1, 1};

        image_t image{image_size.x, image_size.y};


        static const auto write_pixel = [&](const RenderResult& res) {

            const auto screen_uv = res.uv * _size;
            const auto pixel_uv = screen_uv.to<png::uint_32>();

            const auto col = res.output.to<rgb_t>();

            image.set_pixel(pixel_uv.x, pixel_uv.y, pixel_t{col.r, col.g, col.b});
        };


        std::for_each(framebuffer.begin(), framebuffer.end(), write_pixel);

        RAYCHEL_LOG("Finished writing pixels");

        const auto full_file_name = _getFullFileName();

        RAYCHEL_LOG("Writing file ", full_file_name);

        image.write(full_file_name);
        file_number++;
    }

    std::string ImageTargetPng::_getFullFileName() const
    {
        std::ostringstream os;

        os << file_name_ << std::setw(padding_width_) << std::setfill('0') << file_number << ".png";

        return os.str();
    }



} 
