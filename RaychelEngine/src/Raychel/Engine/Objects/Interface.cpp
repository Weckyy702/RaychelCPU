#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Raychel.h"

namespace Raychel {

    vec3 SdObject::get_direction(const vec3& p) const
    {
        return transform_.position-p;
    }

    color SdObject::get_surface_color(const ShadingData& data) const
    {
        return color(data.ray_depth / 5.0);
        //return material_->get_surface_color(data);
    }

}