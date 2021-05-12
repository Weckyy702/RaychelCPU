#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H

#include "Interface.h"

namespace Raychel {
    
    struct SdSphere : public SdObject
    {

        SdSphere(const ObjectData& _d, float _r)
            :SdObject{_d}, radius{_r}
        {}

        SdSphere(SdSphere&& rhs) noexcept
            :SdObject{makeObjectData(std::move(rhs))}, radius{rhs.radius}
        {}

        float eval(const vec3&) const override;

        private:
            float radius=0;
    };

}


#endif //RAYCHEL_SDOBJECT_H