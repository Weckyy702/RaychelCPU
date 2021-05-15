#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Raychel.h"

namespace Raychel {

    vec3 SdObject::getDirectionToObject(const vec3& p) const
    {
        return transform().position-p;
    }

    color SdObject::getSurfaceColor(const ShadingData& data) const
    {
        return material()->getSurfaceColor(data);
    }

    void SdObject::onRendererAttached(const not_null<RaymarchRenderer*> new_renderer){
        material()->setParentRenderer(new_renderer);
    }

}