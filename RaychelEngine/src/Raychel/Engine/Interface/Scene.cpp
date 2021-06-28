#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Rendering/Renderer.h"

namespace Raychel {

    Scene::Scene()
    {
        //NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        renderer_.reset(new RenderController{*this});
    }

    RenderController& Scene::get_renderer() const
    {
        return *renderer_;
    }

    CubeTexture<color>& Scene::set_background_texture(const CubeTexture<color>& texture)
    {
        background_texture_ = texture;
        return background_texture_;
    }

    Camera& Scene::set_camera(const Camera& cam)
    {
        cam_ = cam;
        return cam_;
    }

    void Scene::_notify_renderer() const noexcept
    {
        renderer_->on_scene_layout_changed();
    }
} // namespace Raychel