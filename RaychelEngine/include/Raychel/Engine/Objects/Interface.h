/**
*\file Interface.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Interface header for Objects classes
*\date 2021-06-25
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
#ifndef SD_OBJECT_INTERFACE_H
#define SD_OBJECT_INTERFACE_H

#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Core/Types.h"
#include "Raychel/Engine/Materials/Interface.h"

namespace Raychel {

    //Interface for Raymarchable Objects
    struct IRaymarchable
    {

        RAYCHEL_MAKE_NONCOPY_NONMOVE(IRaymarchable);

    protected:
        IRaymarchable() = default;

    public:
        [[nodiscard]] virtual float eval(const vec3&) const = 0;

        [[nodiscard]] virtual vec3 getDirectionToObject(const vec3&) const = 0;

        [[nodiscard]] virtual color getSurfaceColor(const PrimaryShadingData&) const = 0;

        virtual void onRendererAttached(const RaymarchRenderer&) = 0;

        virtual ~IRaymarchable() = default;
    };

    //Base class for Objects
    class SdObject : public IRaymarchable
    {
    public:
        RAYCHEL_MAKE_NONCOPY_NONMOVE(SdObject);

        RAYCHEL_EXPORT [[nodiscard]] vec3 getDirectionToObject(const vec3& p) const override;

        RAYCHEL_EXPORT [[nodiscard]] color getSurfaceColor(const PrimaryShadingData& data) const override;

        RAYCHEL_EXPORT void onRendererAttached(const RaymarchRenderer& new_renderer) override;

        ~SdObject() override = default;

    protected:
        explicit SdObject(ObjectData&& _data) : transform_{_data.t}, material_{std::move(_data.mat)}
        {}

        [[nodiscard]] inline const Transform& transform() const
        {
            return transform_;
        }
        [[nodiscard]] inline const IMaterial_p& material() const
        {
            return material_;
        }

    private:
        Transform transform_;
        IMaterial_p material_{};
    };

    template <typename Mat>
    ObjectData make_object_data(const Transform& transform, Mat&& mat)
    {
        return ObjectData{transform, std::make_unique<Mat>(std::forward<Mat>(mat))};
    }

} // namespace Raychel

#endif //SD_OBJECT_INTERFACE_H