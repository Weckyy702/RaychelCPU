#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H
#pragma once

#include "Interface.h"

namespace Raychel {
    
    struct SdSphere : public SdObject
    {

        SdSphere(const ObjectData& _d, double _r)
            :SdObject{_d}, radius{_r}
        {}

        SdSphere(SdSphere&& rhs)
            :SdObject{{rhs.transform_}}, radius{rhs.radius}
        {}

        double eval(const vec3&) const override;

        private:
            double radius=0;
    };

}


#endif //RAYCHEL_SDOBJECT_H