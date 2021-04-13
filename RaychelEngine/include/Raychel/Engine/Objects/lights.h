#ifndef RAYCHEL_LIGHTS_H
#define RAYCHEL_LIGHTS_H

#include "Interface.h"

namespace Raychel {

    struct PointLight : public LightData
    {
        PointLight(const Transform& _t, const color& _c, float _b, float _sz)
            :LightData(_t, _c, _b, _sz)
        {}

        
    };

}

#endif //RAYCHEL_LIGHTS_H