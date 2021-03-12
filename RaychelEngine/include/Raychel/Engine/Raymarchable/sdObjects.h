#ifndef RAYCHEL_SDOBJECT_H
#define RAYCHEL_SDOBJECT_H
#pragma once

#include "Interface.h"

namespace Raychel {
    
    struct SdSphere : public IRaymarchable
    {

        SdSphere(const ObjectData& _t, double _r)
        {}

        double eval(const vec3&) const override;

        vec3 get_direction(const vec3&) const override;

        private:
            Transform transform;
            double radius=0;
    };

}


#endif //RAYCHEL_SDOBJECT_H