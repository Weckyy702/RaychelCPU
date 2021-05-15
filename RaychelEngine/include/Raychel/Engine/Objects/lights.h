#ifndef RAYCHEL_LIGHTS_H
#define RAYCHEL_LIGHTS_H

#include "Interface.h"

namespace Raychel {

    class PointLight : public SdLamp
    {
    public:
        PointLight(const Transform& t, const LampData& data)
            :SdLamp(data), transform_{t}
        {}

    private:
        Transform transform_;
    };

}

#endif //RAYCHEL_LIGHTS_H