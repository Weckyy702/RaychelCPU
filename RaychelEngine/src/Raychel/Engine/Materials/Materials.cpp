#include "Raychel/Engine/Materials/Materials.h"

namespace Raychel {

    void DiffuseMaterial::initializeTextureProviders(const vec3&, const vec3&)
    {
        RAYCHEL_LOG("Initializing texture providers");
    }

    color DiffuseMaterial::getSurfaceColor(const ShadingData& data) const
    {
        return albedo_(data.surface_point, data.hit_normal);
    }

}