/**
*\file RenderTarget.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Render targets
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
#ifndef RAYCHEL_RENDER_TARGET_H
#define RAYCHEL_RENDER_TARGET_H
#pragma once

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    /**
    *\brief Abstract base for render targets. The rendered image will be written in here as a texture of colors
    *
    */
    class RenderTarget {

    protected:

        RenderTarget(const vec2i& size)
            :output_size_{size}
        {}

    public:
        inline vec2i size() const noexcept
        {
            return output_size_;
        }

        /**
        *\brief Prepare the target for writing an individual framebuffer. Called right before writeFramebuffer()
        *
        *\note Implementation is optional
        */
        virtual void prepareFramebufferWrite(){}

        /**
        *\brief Write the provided framebuffer into the target
        *
        *\param framebuffer Framebuffer to write
        */
        virtual void writeFramebuffer(const Texture<RenderResult>& framebuffer)=0;

        /**
        *\brief Finish up writing the framebuffer. Called right after writeFramebuffer()
        *
        *\note Implementation is optional
        */
        virtual void finishFramebufferWrite(){}

        virtual ~RenderTarget()=default;
    
    private:
        vec2i output_size_;

    };

    inline void operator<<(RenderTarget& t, const Texture<RenderResult>& framebuffer) {
        t.writeFramebuffer(framebuffer);
    }

}

#endif //RAYCHEL_RENDER_TARGET_H