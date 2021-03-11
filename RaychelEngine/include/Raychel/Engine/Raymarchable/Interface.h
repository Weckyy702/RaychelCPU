#ifndef SD_OBJECT_INTERFACE_H
#define SD_OBJECT_INTERFACE_H
#pragma once

#include <functional>
#include "Raychel/Core/Types.h"

namespace Raychel {
    
    //type-deleted interface for SDF functors
    struct _sdCallable
    {

        template<typename T>
        _sdCallable(T&& _obj)
        {
            do_call = [](const void* obj, const vec3& v) {
                return static_cast<const T*>(obj)->eval(v);
            };

            do_delete = [](void* obj) {
                delete static_cast<T*>(obj);
            };

            obj_ = new T(std::forward<T>(_obj));
        }

        double eval (const vec3& v) const
        {
            return do_call(obj_, v);
        }

        

        ~_sdCallable()
        {
            do_delete(obj_);
        }

        private:
            typedef double(*sdf_t)(const void*, const vec3&);
            typedef void(*destructor_t)(void*);

            void* obj_;
            sdf_t do_call = nullptr;
            destructor_t do_delete = nullptr;
    };

}


#endif //SD_OBJECT_INTERFACE_H