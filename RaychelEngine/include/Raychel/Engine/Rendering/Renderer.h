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

            std::vector<RenderResult> getRenderedImage() const;

        private:
            //Scene* current_scene=nullptr;

            std::vector<RaymarchRequest> requests_;
    };

} 

#endif //RAYCHEL_RENDERER_H