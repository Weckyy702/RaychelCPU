/**
*\file Forward.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for forward declarations
*\date 2021-03-24
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
#ifndef RAYCHEL_FORWARD_H
#define RAYCHEL_FORWARD_H

namespace Raychel {

    //Image Texture
    template<typename T>
    class Texture;

    //Wrapper for either an Image or procedural Texture
    template<typename T>
    class TextureProvider;

    //Wrapper for either a Cube Map or a procedural Texture
    template<typename T>
    class CubeTexture;

    class Scene;

    class Camera;

    struct IRaymarchable;
    struct IMaterial;

    class Material;

    class RaymarchRenderer;
}

#endif //RAYCHEL_FORWARD_H