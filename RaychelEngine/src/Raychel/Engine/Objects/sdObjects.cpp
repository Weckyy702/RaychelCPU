#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Raychel.h"

float Raychel::SdPlane::eval(const vec3& _p) const noexcept
{
    return std::abs(dot(_p, normal_) - offset_along_normal_);
}