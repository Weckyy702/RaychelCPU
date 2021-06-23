#include "Raychel/Engine/Interface/Camera.h"

namespace Raychel {

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
        return normalize(g_right * transform_.rotation);
    }

    void Camera::set_roll(float a) noexcept
    {
        transform_.rotation = Quaternion(forward(), a);
    }

    void Camera::set_pitch(float a) noexcept
    {
        transform_.rotation = Quaternion(right(), a);
    }

    void Camera::set_yaw(float a) noexcept
    {
        transform_.rotation = Quaternion(up(), a);
    }

    Quaternion Camera::update_roll(float da) noexcept
    {
        transform_.rotation *= Quaternion(forward(), da);
        return transform_.rotation;
    }

    Quaternion Camera::update_pitch(float da) noexcept
    {
        transform_.rotation *= Quaternion(right(), da);
        return transform_.rotation;
    }

    Quaternion Camera::update_yaw(float da) noexcept
    {
        transform_.rotation *= Quaternion(up(), da);
        return transform_.rotation;
    }

} // namespace Raychel