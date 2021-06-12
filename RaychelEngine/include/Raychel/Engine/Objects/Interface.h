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
        virtual float eval(const vec3&) const = 0;

        virtual vec3 getDirectionToObject(const vec3&) const = 0;

        virtual color getSurfaceColor(const ShadingData&) const = 0;

        virtual void onRendererAttached(const RaymarchRenderer&) = 0;

        virtual ~IRaymarchable() = default;
    };

    //Base class for Objects
    class SdObject : public IRaymarchable
    {
    public:
        RAYCHEL_MAKE_NONCOPY_NONMOVE(SdObject);

        color getSurfaceColor(const ShadingData& data) const override;

        void onRendererAttached(const RaymarchRenderer& new_renderer) override;

        vec3 getDirectionToObject(const vec3& p) const override;

        virtual ~SdObject() = default;

    protected:
        SdObject(ObjectData&& _data) : transform_{_data.t}, material_{std::move(_data.mat)}
        {}

        const Transform& transform() const
        {
            return transform_;
        }
        const IMaterial_p& material() const
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

    class SdLamp : public IRaymarchable
    {
    public:
        RAYCHEL_MAKE_NONCOPY_NONMOVE(SdLamp);

    protected:
        SdLamp(const LampData& _data) : color_{_data.c}, brightness_{_data.b}, size_{_data.sz}
        {}

        color lampColor() const noexcept
        {
            return color_;
        }
        float brightness() const noexcept
        {
            return brightness_;
        }
        float size() const noexcept
        {
            return size_;
        }

        virtual ~SdLamp() = 0;

    private:
        color color_;
        float brightness_{1.0};
        float size_{0.0};
    };

} // namespace Raychel

#endif //SD_OBJECT_INTERFACE_H