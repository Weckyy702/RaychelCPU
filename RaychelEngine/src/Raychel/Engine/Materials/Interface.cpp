#include "Raychel/Engine/Materials/Interface.h"

namespace Raychel {

    void Material::setParentRenderer(not_null<RaymarchRenderer*> new_renderer)
    {
            parent_renderer_ = new_renderer;
    }

}