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



    void Camera::setRoll(double a) noexcept
    {
        transform_.rotation = Quaternion(forward(), a);
    }

    void Camera::setPitch(double a) noexcept
    {
        transform_.rotation = Quaternion(right(), a);
    }

    void Camera::setYaw(double a) noexcept
    {
        transform_.rotation = Quaternion(up(), a);
    }

    Quaternion Camera::updateRoll(double da) noexcept
    {
        transform_.rotation *= Quaternion(forward(), da);
        return transform_.rotation;
    }

    Quaternion Camera::updatePitch(double da) noexcept
    {
        transform_.rotation *= Quaternion(right(), da);
        return transform_.rotation;
    }

    Quaternion Camera::updateYaw(double da) noexcept
    {
        transform_.rotation *= Quaternion(up(), da);
        return transform_.rotation;
    }

}