#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H

#include "Interface.h"

namespace Raychel {

    struct SdSphere : public SdObject
    {

        SdSphere(ObjectData&& data, float _r) : SdObject{std::move(data)}, radius{_r}
        {}

        float eval(const vec3& p) const override;

    private:
        float radius = 0;
    };

} // namespace Raychel

#endif //RAYCHEL_SDOBJECT_H