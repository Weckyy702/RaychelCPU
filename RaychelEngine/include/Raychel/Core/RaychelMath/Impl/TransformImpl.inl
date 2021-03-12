#include "../Transform.h"

namespace Raychel {

    template<typename T>
    auto TransformImp<T>::apply(const vec3& p) const -> vec3
    {
        return (position - p) * rotation;
    }

}