#ifndef SD_OBJECT_INTERFACE_H
#define SD_OBJECT_INTERFACE_H
#pragma once

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    //Interface for Raymarchable Objects
    struct IRaymarchable
    {

        IRaymarchable()=default;

        IRaymarchable(const IRaymarchable&)=delete;
        IRaymarchable(IRaymarchable&&)=delete;

        IRaymarchable& operator=(const IRaymarchable&)=delete;
        IRaymarchable& operator=(IRaymarchable&&)=delete;


        virtual double eval(const vec3&) const=0;

        virtual vec3 get_direction(const vec3&) const=0;

        virtual color get_surface_color(const ShadingData&) const=0;
    };


    //Base class for Raymarchable Objects
    class SdObject : public IRaymarchable
    {
    
    public:
        SdObject(const ObjectData& _data)
            :transform_{_data.t} //, material_{_data.mat}
        {}

    vec3 get_direction(const vec3& p) const override;

    color get_surface_color(const ShadingData& data) const override;

    protected:
        Transform transform_;
        //IMaterial_p material_;
    };

    class SdLamp : public IRaymarchable
    {

    public:
        SdLamp(const LampData& _data)
            :lampColor{_data.c}, lampBrightness{_data.b}, lampSize{_data.sz}
        {}

    protected:
        color lampColor;
        double lampBrightness=1.0;
        double lampSize=1.0;
    };

}


#endif //SD_OBJECT_INTERFACE_H