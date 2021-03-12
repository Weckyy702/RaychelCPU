#ifndef RAYCHEL_TRANSFORM_H
#define RAYCHEL_TRANSFORM_H

#pragma once

#include "../utils.h"
#include "vec3.h"
#include "Quaternion.h"

namespace Raychel
{
    
    template<RAYCHEL_NUMBER _number>
    struct TransformImp
    {

        //this ugly mess will have to stay until C++20
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

    private:

        RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::vec3<T> requires T to be of arithmetic type!");
        using vec3 = vec3Imp<value_type>;
        using Quaternion = QuaternionImp<value_type>;
    
    public:

        TransformImp()=default;

        TransformImp(const vec3& pos)
            :position{ pos }
        {}

        TransformImp(const Quaternion& rot)
            :rotation{ rot }
        {}

        TransformImp(const vec3& pos, const Quaternion& rot)
            :position{ pos }, rotation( rot )
        {}

        vec3 apply(const vec3&) const;

        vec3 position;
        Quaternion rotation;

    };

}


#endif //RAYCHEL_TRANSFORM_H