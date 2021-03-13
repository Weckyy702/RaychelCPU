#ifndef RAYCHEL_RENDERER_H
#define RAYCHEL_RENDERER_H

#include "Raychel/Core/Types.h"
#include "Raychel/Core/LinkTypes.h"

namespace Raychel
{

    class RenderController
    {
        public:

            RenderController()=default;

            vec2i setOutputSize(const vec2i& newSize);

            void setCurrentScene(const not_null<Scene*> newScene);

            Texture<RenderResult> getRenderedImage() const;

        private:

            void _refillRequestBuffer(const vec2i& new_size);

            RaymarchRequest _getRootRequest(size_t x, size_t y) const;

            Scene* current_scene_ =nullptr;
            vec2i output_size_;

            std::vector<RaymarchRequest> requests_;
    };

} 

#endif //RAYCHEL_RENDERER_H