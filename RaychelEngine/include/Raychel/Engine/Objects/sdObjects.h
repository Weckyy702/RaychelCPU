#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H

#include "Interface.h"

namespace Raychel {

    class SdSphere : public SdObject
    {
    public:
        SdSphere(ObjectData&& data, float _r) : SdObject{std::move(data)}, radius{_r}
        {}

        [[nodiscard]] float eval(const vec3& p) const noexcept override
        {
            return dist(p, transform().position) - radius;
        }

    private:
        float radius = 0;
    };

    class SdPlane : public SdObject
    {
    public:
        SdPlane(ObjectData&& data, const vec3& normal) : SdObject{std::move(data)}, normal_{normalize(normal)}
        {}

        SdPlane(ObjectData&& data, const vec3& normal, float offset_along_normal)
            : SdObject{std::move(data)}, normal_{normalize(normal)}, offset_along_normal_(offset_along_normal)
        {}

        [[nodiscard]]inline  float eval(const vec3& p) const noexcept override
        {
            return std::abs(dot(p, normal_) - offset_along_normal_);
        }

    private:
        normalized3 normal_;
        float offset_along_normal_ = 0.0F;
    };

} // namespace Raychel

#endif //RAYCHEL_SDOBJECT_H