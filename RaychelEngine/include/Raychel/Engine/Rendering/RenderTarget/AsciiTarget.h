/**
*\file AsciiTarget.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for ASCII image targets
*\date 2021-04-13
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
#ifndef RAYCHEL_ASCII_TARGET_H
#define RAYCHEL_ASCII_TARGET_H

#include "Raychel/Core/utils.h"
#include "RenderTarget.h"

namespace Raychel {

    class AsciiTarget : public RenderTarget {

        public:
            AsciiTarget(const vec2i& size);
            AsciiTarget(const vec2i& size, const std::vector<char>& char_set);

            void writeFramebuffer(const Texture<RenderResult>& framebuffer) override;

            void finishFramebufferWrite() override;

            ~AsciiTarget() override;

        private:

            void _init_ncurses() const;

            const std::vector<char> character_set_ = {'.', ':', ';', '~', '=', '#', '0', 'B', '8', '%', '&'};
    };

}

#endif //!RAYCHEL_ASCII_TARGET_H