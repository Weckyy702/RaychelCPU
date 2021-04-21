#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Raychel.h"

namespace Raychel {

    vec3 SdObject::getDirection(const vec3& p) const
    {
        return transform_.position-p;
    }

    color SdObject::getSurfaceColor(const ShadingData& data) const
    {
        return material_->getSurfaceColor(data);
    }

    void SdObject::onRendererAttached(const not_null<RaymarchRenderer*> new_renderer){
        material_->setParentRenderer(new_renderer);
    }

}