#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H

#include "Interface.h"

namespace Raychel {
    
    struct SdSphere : public SdObject
    {

        SdSphere(const ObjectData& _d, float _r)
            :SdObject{_d}, radius{_r}
        {}

        float eval(const vec3& p) const override;

        private:
            float radius=0;
    };

}


#endif //RAYCHEL_SDOBJECT_H