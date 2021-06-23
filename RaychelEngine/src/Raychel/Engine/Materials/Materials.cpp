#include "Raychel/Engine/Materials/Materials.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"

namespace Raychel {

    void DiffuseMaterial::initializeTextureProviders(const vec3& /*parent_position*/, const vec3& /*parent_size*/)
    {
        RAYCHEL_LOG("Initializing texture providers");
    }

    color DiffuseMaterial::getSurfaceColor(const PrimaryShadingData& data) const
    {
        return parent_renderer()->shade_diffuse(
            {{data.surface_point, data.hit_normal, data.in_direction, data.recursion_depth},
             albedo_(data.surface_point, data.hit_normal)});
    }

} // namespace Raychel