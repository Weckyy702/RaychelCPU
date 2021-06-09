#include "Raychel/Engine/Interface/Scene.h"

namespace Raychel {

    CubeTexture<color>& Scene::setBackgroundTexture(const CubeTexture<color>& texture)
    {
        background_texture_ = texture;
        return background_texture_;
    }

    Camera& Scene::setCamera(const Camera& cam)
    {
        cam_ = cam;
        return cam_;
    }
} // namespace Raychel