#ifndef RAYCHEL_SHADING_H
#define RAYCHEL_SHADING_H

#include <atomic>

#include "Raychel/Core/LinkTypes.h"
#include "Raychel/Core/Types.h"
namespace Raychel {

    class RaymarchRenderer
    {

    public:
        RaymarchRenderer() = default;

        RAYCHEL_EXPORT void setRenderSize(const vec2i& new_size);

        RAYCHEL_EXPORT void setSceneData(not_null<std::vector<IRaymarchable_p>*> objects, not_null<CubeTexture<color>*> background_texture);

        RAYCHEL_EXPORT std::optional<Texture<RenderResult>> renderImage(const Camera& cam);

    private:
        RAYCHEL_EXPORT void set_scene_callback_renderer();

        RAYCHEL_EXPORT void _refillRequestBuffer();

        RAYCHEL_EXPORT RaymarchData _getRootRequest(size_t x, size_t y) const;

        RAYCHEL_EXPORT bool _renderToTexture(Texture<RenderResult>& output) const;

        RAYCHEL_EXPORT void _setupCamData(const Camera& cam) noexcept;

//these functions are defined in RaymarchMath.cpp
#pragma region Raymarching functions

        RAYCHEL_EXPORT vec3 _getRayDirectionFromUV(const vec2&) const noexcept;

        RAYCHEL_EXPORT RenderResult _raymarchFunction(const RaymarchData& req) const noexcept;

        RAYCHEL_EXPORT color getShadedColor(const vec3& origin, const vec3& direction, size_t recursion_depth) const;

        RAYCHEL_EXPORT RaymarchHitInfo getHitInfo(
            const vec3& origin, const vec3& direction, float depth, size_t num_ray_steps, size_t recursion_depth) const noexcept;

        RAYCHEL_EXPORT vec3 getNormal(const vec3& p) const noexcept;

        RAYCHEL_EXPORT IRaymarchable* getHitObject(const vec3& p) const noexcept;

        RAYCHEL_EXPORT float sdScene(const vec3& p) const;

        RAYCHEL_EXPORT bool raymarch(
            const vec3& origin, const normalized3& direction, float max_depth, float* out_depth,
            size_t* out_num_ray_steps) const noexcept;

#pragma endregion

        RAYCHEL_EXPORT vec2 _getScreenspaceUV(const vec2& uv) const noexcept;

        vec2i output_size_;
        float aspect_ratio = 0.0;

        //Non-owning references to scene specific data
        const std::vector<IRaymarchable_p>* objects_ = nullptr;
        const CubeTexture<color>* background_texture_ = nullptr;

        //Buffer of all UVs for which to raymarch
        std::vector<RaymarchData> requests_;

        //size of this struct should be less than a cache line.
        //buffer forward, right and up vectors here
        struct
        {
            vec3 position, forward, right, up;
            float zoom{0.0};
        } cam_data_;

        //size of this struct should be less than a cache line.
        //these values are dependent on RaymarchOptions::_epsilon
        struct
        {
            size_t max_recursion_depth{5};

            float max_ray_depth{100.0F};

            float distance_bias{1e-4F};
            float normal_bias{1e-5F};
            float surface_bias{5e-4F};
        } raymarch_data_;

        mutable std::atomic_bool failed_{false};
        mutable exception_context current_exception_{"", "", false};
    };

} // namespace Raychel

#endif //RAYCHEL_SHADING_H