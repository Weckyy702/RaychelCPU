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
    };



    struct SdObject : IRaymarchable
    {

        SdObject(const ObjectData& _data)
        {}

        Transform transform;
    };

    struct SdLamp : IRaymarchable
    {

        SdLamp(const LampData& _data)
        {}
    };

}


#endif //SD_OBJECT_INTERFACE_H