#ifndef RAYCHEL_SHADING_H
#define RAYCHEL_SHADING_H

#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    class RaymarchRenderer {

    public:

        RaymarchRenderer()=default;

        void setRenderSize(const vec2i& new_size);

        void setSceneData(  const not_null<std::vector<IRaymarchable_p>*> objects/*,
                            const not_null<TextureProvider<color>*> background_texture*/);

        Texture<RenderResult> renderImage(const Camera& cam);

    private:

        void _refillRequestBuffer();

        RaymarchData _getRootRequest(size_t x, size_t y, double ar) const;

        void _renderToTexture(Texture<RenderResult>& output) const;

        void _setupCamData(const Camera& cam) noexcept;

        #pragma region Raymarching functions

        vec3 _getRayDirectionFromUV(const vec2&) const noexcept;

        RenderResult _raymarchFunction(const RaymarchData& req) const;

        double sdScene(const vec3& p) const;

        bool raymarch(const vec3& origin, const vec3& direction, double max_depth, double* out_depth) const noexcept;

        #pragma endregion


        vec2i output_size_;

        //Non-owning references to scene specific data
        std::vector<IRaymarchable_p> const* objects_;
        TextureProvider<color> const* background_;

        //Buffer of all UVs for which to raymarch
        std::vector<RaymarchData> requests_;

        //buffer forward, right and up vectors here
        struct {
            vec3 position, forward, right, up;
            double zoom;
        } cam_data_;

    };

}

#endif //RAYCHEL_SHADING_H