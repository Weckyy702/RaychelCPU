/**
*\file Materials.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for default materials
*\date 2021-04-20
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
#ifndef RAYCHEL_MATERIALS_H
#define RAYCHEL_MATERIALS_H

#include "Interface.h"
#include "Raychel/Core/utils.h"
#include "Raychel/Misc/Texture/TextureProvider.h"

namespace Raychel {

    /**
    *\brief Perfectly rough Material
    *
    */
    class DiffuseMaterial final : public Material {

    public:

        DiffuseMaterial(const TextureProvider<color>& albedo)
            :albedo_{albedo}
        {}

        DiffuseMaterial(DiffuseMaterial&& rhs)
            :albedo_{std::move(rhs.albedo_)}
        {}

        void initializeTextureProviders(const vec3& parent_position, const vec3& parent_bounding_box) override;

        color getSurfaceColor(const ShadingData& data) const override;

        ~DiffuseMaterial() override=default;

    private:
        TextureProvider<color> albedo_;
    };

}

#endif //!RAYCHEL_MATERIALS_H