#include "Raychel/Engine/Materials/Interface.h"

namespace Raychel {

    void Material::setParentRenderer(const RaymarchRenderer& new_renderer)
    {
        parent_renderer_ = &new_renderer;
    }

} // namespace Raychel