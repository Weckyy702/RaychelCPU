#include "Raychel/Engine/Interface/Camera.h"
#include <cmath>
#include <cassert>

namespace Raychel {

    static constexpr vec3 g_forward = vec3{ 0, 0, 1 };
    static constexpr vec3 g_up = vec3{ 0, 1, 0 };

    //cos(45°) with a little padding
    static constexpr double cos_45_degrees = 0.707106781187 * 0.99;

    vec3 Camera::forward() const noexcept
    {
        return normalize(g_forward * transform_.rotation);
    }

    vec3 Camera::up() const noexcept
    {
        return normalize(g_up * transform_.rotation);
    }

    vec3 Camera::right() const noexcept
    {
        return -cross(forward(), up());
    }

}