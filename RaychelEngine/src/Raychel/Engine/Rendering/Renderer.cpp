#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"

namespace Raychel {

    vec2i RenderController::setOutputSize(const vec2i& new_size)
    {
        output_size_ = new_size;

        renderer_.setRenderSize(new_size /* * RenderOptions.AA_factor*/);

        return output_size_;
    }

    void RenderController::setCurrentScene(const not_null<Scene*> new_scene)
    {
        current_scene_ = new_scene;
        renderer_.setSceneData(&current_scene_->objects_, &current_scene_->background_texture_);
    }

    std::optional<Texture<RenderResult>> RenderController::getImageRendered()
    {
        //TODO implement postprocessing
        return renderer_.renderImage(current_scene_->cam_);
    }

} // namespace Raychel