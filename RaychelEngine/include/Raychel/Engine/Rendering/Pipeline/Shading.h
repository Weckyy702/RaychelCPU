#ifndef RAYCHEL_SHADING_H
#define RAYCHEL_SHADING_H

#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    class RaymarchRenderer {

    public:

        RaymarchRenderer()=default;

        void setRenderSize(const vec2i& new_size);

        void setSceneData(  const not_null<Camera*> cam,
                            const not_null<std::vector<IRaymarchable_p>*> objects,
                            const not_null<TextureProvider<color>*> background_texture);

        Texture<RenderResult> renderImage() const;

    private:

        void _refillRequestBuffer();

        RaymarchRequest _getRootRequest(size_t x, size_t y) const;

        void _renderToTexture(Texture<RenderResult>& output) const;

        vec2i output_size_;

        //Non-owning references to scene specific data
        std::vector<IRaymarchable_p>* objects_;
        Camera* cam_;
        TextureProvider<color>* background_;

        //Buffer of all UVs for which to raymarch
        std::vector<RaymarchRequest> requests_;

    };

}

#endif //RAYCHEL_SHADING_H