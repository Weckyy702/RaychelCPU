#ifndef RAYCHEL_CAMERA_H
#define RAYCHEL_CAMERA_H

#include <array>
#include "Raychel/Core/Types.h"

namespace Raychel {

    class Camera {

    public:

        Camera()=default;

        Camera(const Transform& _t, double _zoom)
            :transform_(_t), zoom_(_zoom)
        {}

        vec3 forward() const noexcept;

        vec3 right() const noexcept;

        vec3 up() const noexcept;

        inline double zoom() const noexcept
        {
            return zoom_;
        }

        friend class RaymarchRenderer;

    //private:

            Transform transform_;
            double zoom_=1.0;

            //double exposure;

            //colors that each channel reacts to. Essential for color bleed etc.
            std::array<color, 3> color_channels_ = {
                color(1, 0, 0),
                color(0, 1, 0),
                color(0, 0, 1)
            };
    };

}

#endif //RAYCHEL_CAMERA_H