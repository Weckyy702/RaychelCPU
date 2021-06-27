#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"

namespace Raychel {

    RenderController::RenderController(const Scene& parent)
        :parent_scene_(parent), renderer_(parent.objects_, parent.lamps_, parent.background_texture_)
    {
        renderer_._set_scene_callback_renderer();
    }

    vec2i RenderController::setOutputSize(const vec2i& new_size)
    {
        output_size_ = new_size;

        renderer_.set_render_size(new_size /* * RenderOptions.AA_factor*/);

        return output_size_;
    }

    std::optional<Texture<RenderResult>> RenderController::getImageRendered()
    {
        //TODO implement postprocessing
        return renderer_.render_image(parent_scene_.cam_);
    }

    void RenderController::on_scene_layout_changed() const
    {
        //possibly recalculate later optimizations
        renderer_._set_scene_callback_renderer();
    }

} // namespace Raychel