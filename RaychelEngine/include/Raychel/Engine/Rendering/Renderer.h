/**
*\file Renderer.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for RenderController class
*\date 2021-06-27
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
#ifndef RAYCHEL_RENDERER_H
#define RAYCHEL_RENDERER_H

#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Core/Types.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Misc/Texture/Texture.h"

namespace Raychel {

    class RenderController
    {
    public:
        RAYCHEL_EXPORT vec2i set_output_size(const vec2i& new_size);

        //will become private later
        RAYCHEL_EXPORT std::optional<Texture<RenderResult>> get_rendered_image();

        RAYCHEL_EXPORT std::optional<Texture<color>> get_postprocessed_image() const;

        void render_image(); //?

    private:
        void on_scene_layout_changed() const;

        RAYCHEL_EXPORT explicit RenderController(const Scene& parent);

        friend class Scene;

        //non-owning reference to current scene
        const Scene& parent_scene_;
        vec2i output_size_;

        RaymarchRenderer renderer_;
        //PostProcessor postprecessor_;
    };

} // namespace Raychel

#endif //RAYCHEL_RENDERER_H