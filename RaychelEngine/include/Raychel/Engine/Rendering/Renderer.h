#ifndef RAYCHEL_RENDERER_H
#define RAYCHEL_RENDERER_H

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"

namespace Raychel
{

    class RenderController
    {
        public:

            RenderController()=default;

            vec2i setOutputSize(const vec2i& newSize);

            void setCurrentScene(const not_null<Scene*> newScene);

            //may become private later
            std::optional<Texture<RenderResult>> getImageRendered();

            std::optional<Texture<color>> getImagePostprocessed() const;

            void renderImage();

        private:

            //non-owning reference to current scene
            Scene* current_scene_ =nullptr;
            vec2i output_size_;

            RaymarchRenderer renderer_;
            //PostProcessor postprecessor_;
    };

} 

#endif //RAYCHEL_RENDERER_H