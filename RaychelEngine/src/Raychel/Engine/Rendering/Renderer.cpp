#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Interface/Scene.h"

namespace Raychel {

    vec2i RenderController::setOutputSize(const vec2i& new_size)
    {
        output_size_ = new_size;

        renderer_.setOutuptSize(new_size);

        return output_size_;
    }



    void RenderController::setCurrentScene(const not_null<Scene*> new_scene) 
    {
        current_scene_ = new_scene;
    }


    Texture<color> RenderController::getImageRendered() const
    {
        
    }

}