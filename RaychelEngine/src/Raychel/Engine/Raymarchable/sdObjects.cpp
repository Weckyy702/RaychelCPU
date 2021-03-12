#include "Raychel/Raychel.h"
#include "Raychel/Engine/Raymarchable/sdObjects.h"

double Raychel::SdSphere::eval(const vec3& _p) const
{
    return dist(_p, transform.position) - radius;
}

Raychel::vec3 Raychel::SdSphere::get_direction(const vec3& p) const
{
    return {};
}