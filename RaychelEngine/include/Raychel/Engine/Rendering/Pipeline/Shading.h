#ifndef RAYCHEL_SHADING_H
#define RAYCHEL_SHADING_H

#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    class RaymarchRenderer {

    public:

        RaymarchRenderer()=default;

        void setObjects(const not_null<std::vector<IRaymarchable_p>*> objects);

        //void setMaterials(const not_null<std::vector<IMaterial_p>*> materials);

        Texture<RenderResult> renderImage(const vec2i& window_size, const Camera& cam) const;

    private:

        void _refillRequestBuffer(const vec2i& new_size);

        RaymarchRequest _getRootRequest(const vec2i& output_size, size_t x, size_t y) const;

        const std::vector<IRaymarchable_p>* objects_;
        //const std::vector<IMaterial_p>* materials_;
        
        std::vector<RaymarchRequest> requests_;

    };

}

#endif //RAYCHEL_SHADING_H