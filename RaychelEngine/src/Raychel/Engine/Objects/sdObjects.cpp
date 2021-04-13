#include "Raychel/Raychel.h"
#include "Raychel/Engine/Objects/sdObjects.h"

float Raychel::SdSphere::eval(const vec3& _p) const
{
    return dist(_p, transform_.position) - radius;
}