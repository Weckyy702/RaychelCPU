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

        RAYCHEL_EXPORT void set_render_size(const vec2i& new_size);

        RAYCHEL_EXPORT void
        set_scene_data(not_null<std::vector<IRaymarchable_p>*> objects, not_null<CubeTexture<color>*> background_texture);

        RAYCHEL_EXPORT std::optional<Texture<RenderResult>> render_image(const Camera& cam);

        RAYCHEL_EXPORT color shade_diffuse(const DiffuseShadingData& data) const noexcept;

    private:
        RAYCHEL_EXPORT explicit RaymarchRenderer(
            const std::vector<IRaymarchable_p>& objects, const std::vector<ILamp_p>& lamps,
            const CubeTexture<color>& background_texture);

        RAYCHEL_EXPORT void _set_scene_callback_renderer() const;

        RAYCHEL_EXPORT void _refill_request_buffer();

        RAYCHEL_EXPORT RaymarchData _get_root_request(size_t x, size_t y) const;

        RAYCHEL_EXPORT bool _render_to_texture(Texture<RenderResult>& output) const;

        RAYCHEL_EXPORT void _setup_cam_data(const Camera& cam) noexcept;

//these functions are defined in RaymarchMath.cpp
#pragma region Raymarching functions

        RAYCHEL_EXPORT vec3 _get_ray_direction_from_UV(const vec2&) const noexcept;

        RAYCHEL_EXPORT RenderResult _raymarch_function(const RaymarchData& req) const noexcept;

        RAYCHEL_EXPORT color get_shaded_color(const vec3& origin, const vec3& direction, size_t recursion_depth) const;

        RAYCHEL_EXPORT RaymarchHitInfo get_hit_info(
            const vec3& origin, const vec3& direction, float depth, size_t num_ray_steps, size_t recursion_depth) const noexcept;

        RAYCHEL_EXPORT vec3 get_normal(const vec3& p) const noexcept;

        RAYCHEL_EXPORT IRaymarchable* get_hit_object(const vec3& p) const noexcept;

        RAYCHEL_EXPORT float sd_scene(const vec3& p) const;

        RAYCHEL_EXPORT bool raymarch(
            const vec3& origin, const normalized3& direction, float max_depth, float* out_depth,
            size_t* out_num_ray_steps) const noexcept;

#pragma endregion

        void _register_render_exception(gsl::czstring<> origin, gsl::czstring<> msg, bool fatal)
        {
            failed_ = true;
            current_exception_ = {msg, origin, fatal};
        }

        vec2i output_size_;
        float aspect_ratio = 0.0;

        //Non-owning references to scene specific data
        const std::vector<IRaymarchable_p>& objects_;
        const std::vector<ILamp_p>& lamps_;
        const CubeTexture<color>& background_texture_;

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
        mutable exception_context current_exception_;
    };

} // namespace Raychel

#endif //RAYCHEL_SHADING_H