#include "Raychel/Engine/Objects/sdObjects.h"
#include "Raychel/Raychel.h"

float Raychel::SdSphere::eval(const vec3& _p) const
{
    return dist(_p, transform().position) - radius;
}