/**
*\file ImageTarget.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for Render target that outputs to a png image
*\date 2021-03-27
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/
#ifndef RAYCHEL_IMAGE_TARGET_H
#define RAYCHEL_IMAGE_TARGET_H

#include <string>

#include "RenderTarget.h"

namespace Raychel {

    /**
    *\brief Render target that will output the provided framebuffer(s) as a png image(/sequence)
    *
    */
    class ImageTargetPng : public RenderTarget
    {

    public:
        /**
        *\brief Construct a new Image Target object
        *
        *\param size Nize of the image(s)
        *\param file_name Name of the image(s)
        */
        ImageTargetPng(const vec2i& size, std::string_view file_name) : RenderTarget{size}, file_name_{file_name}
        {}

        /**
        *\brief Construct a new Image Target object
        *
        *\param size Size of the image(s)
        *\param file_name Name of the image(s)
        *\param padding_width If multiple images are written, pad each file name to file_name('#'*padding_width).png
        */
        ImageTargetPng(const vec2i size, std::string_view file_name, std::uint8_t padding_width)
            : RenderTarget(size), file_name_{file_name}, padding_width_{padding_width}
        {}

        /**
        *\brief Save the provided framebuffer as a png image
        *
        *\param framebuffer the framebuffer to be saved
        */
        void writeFramebuffer(const Texture<RenderResult>& framebuffer) override;

    private:
        [[nodiscard]] std::string _getFullFileName() const;

        std::string file_name_;
        size_t file_number = 0;
        const std::uint8_t padding_width_ = 3;
    };

} // namespace Raychel

#endif //RAYCHEL_IMAGE_TARGET_H