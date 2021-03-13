#ifndef SD_OBJECT_INTERFACE_H
#define SD_OBJECT_INTERFACE_H
#pragma once

#include <atomic>

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    //Interface for Raymarchable Objects
    struct IRaymarchable
    {

        IRaymarchable()
            :obj_index_{instance_count++}
        {}

        IRaymarchable(const IRaymarchable&)=delete;
        IRaymarchable(IRaymarchable&&)=delete;

        IRaymarchable& operator=(const IRaymarchable&)=delete;
        IRaymarchable& operator=(IRaymarchable&&)=delete;


        virtual double eval(const vec3&) const=0;

        virtual vec3 get_direction(const vec3&) const=0;

        size_t get_object_id() const {
            return obj_index_;
        }

        private:
            static std::atomic_size_t instance_count;
            const size_t obj_index_;
    };



    struct SdObject : IRaymarchable
    {

        SdObject(const ObjectData& _data)
            :transform{_data.t}
        {}

        Transform transform;
    };

    struct SdLamp : IRaymarchable
    {

        SdLamp(const LampData& _data)
            :lampColor{_data.c}, lampBrightness{_data.b}, lampSize{_data.sz}
        {}

        color lampColor;
        double lampBrightness=1.0;
        double lampSize=1.0;
    };

}


#endif //SD_OBJECT_INTERFACE_H