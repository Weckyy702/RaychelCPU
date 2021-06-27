#define TBB_SUPPRESS_DEPRECATED_MESSAGES 1

#include <algorithm>
#include <execution>
#include <functional>
#include <limits>

#include "Raychel/Core/Types.h"
#include "Raychel/Engine/Interface/Camera.h"
#include "Raychel/Engine/Interface/Scene.h"
#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {

    color RaymarchRenderer::shade_diffuse(const DiffuseShadingData& data) const noexcept
    {
        const color lighting = get_diffuse_lighting(data.surface_point, data.hit_normal, data.recursion_depth);
        return data.albedo * lighting;
    }

#pragma region Setup functions

    RaymarchRenderer::RaymarchRenderer(
        const std::vector<IRaymarchable_p>& objects, const std::vector<ILamp_p>& lamps,
        const CubeTexture<color>& background_texture)
        : objects_{objects}, lamps_{lamps}, background_texture_{background_texture}
    {}

    void RaymarchRenderer::set_render_size(const vec2i& new_size)
    {
        RAYCHEL_LOG(
            "Setting render output size to ",
            new_size,
            " (aspect ratio of ",
            static_cast<number_t>(new_size.x) / static_cast<number_t>(new_size.y),
            ")");
        output_size_ = new_size;
        _refill_request_buffer();
    }

    void RaymarchRenderer::_set_scene_callback_renderer() const
    {
        for (const auto& obj : objects_) {
            obj->onRendererAttached(*this);
        }
    }

    void RaymarchRenderer::_refill_request_buffer()
    {
        RAYCHEL_LOG("Refilling request buffer to ", output_size_.x * output_size_.y, " pixels");

        requests_.clear();
        size_t request_count = output_size_.x * output_size_.y;
        requests_.reserve(request_count);

        aspect_ratio = static_cast<number_t>(output_size_.x) / static_cast<number_t>(output_size_.y);

        for (auto i = 0U; i < output_size_.y; i++) {
            for (auto j = 0U; j < output_size_.x; j++) {
                requests_.push_back(_get_root_request(j, i));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchData RaymarchRenderer::_get_root_request(size_t x, size_t y) const
    {
        //generate UVs in range [-0.5; 0.5]

        float dx = (static_cast<number_t>(x) / static_cast<number_t>(output_size_.x)) - 0.5F;
        float dy = (static_cast<number_t>(y) / static_cast<number_t>(output_size_.y)) - 0.5F;

        //handle non-square aspect ratios
        if (aspect_ratio > 1.0) {
            dx *= aspect_ratio;
        } else {
            dy /= aspect_ratio;
        }

        return {vec2{dx, dy}};
    }

#pragma endregion

#pragma region Render functions

    std::optional<Texture<RenderResult>> RaymarchRenderer::render_image(const Camera& cam)
    {
        _setup_cam_data(cam);

        Texture<RenderResult> output{output_size_};

        if (!_render_to_texture(output)) {
            Logger::error(
                "Image rendering failed with error: ", current_exception_.what(), "at (", current_exception_.origin(), ")!\n");
            //TODO: customizable error handling
            return std::nullopt;
        }

        return output;
    }

    bool RaymarchRenderer::_render_to_texture(Texture<RenderResult>& output_texture) const
    {

        using namespace std::placeholders;

        static const auto f = [this](const RaymarchData& req) { return _raymarch_function(req); };

        RAYCHEL_LOG("Starting render...");

        std::transform(std::execution::par, requests_.cbegin(), requests_.cend(), output_texture.begin(), f);

        RAYCHEL_LOG("Finished render!");
        return !failed_;
    }

    void RaymarchRenderer::_setup_cam_data(const Camera& cam) noexcept
    {
        cam_data_.position = cam.transform_.position;
        cam_data_.forward = cam.forward();
        cam_data_.right = cam.right();
        cam_data_.up = cam.up();
        cam_data_.zoom = cam.zoom();

        RAYCHEL_LOG(
            "Rendering with Camera at ",
            cam_data_.position,
            ", with local coordinate frame: { +x: ",
            cam_data_.right,
            ", +y: ",
            cam_data_.up,
            ", +z: ",
            cam_data_.forward,
            " }");
    }

    vec2 RaymarchRenderer::_get_screenspace_UV(const vec2& uv) const noexcept
    {
        vec2 actual_uv = uv;

        if (aspect_ratio > 1.0) {
            actual_uv.x /= aspect_ratio;
        } else {
            actual_uv.y *= aspect_ratio;
        }

        actual_uv += vec2{0.5F, 0.5F};

        actual_uv.y = 1.0F - actual_uv.y;

        return actual_uv;
    }

#pragma endregion

#pragma region Shading functions

    //Lambertian term for the rendering equation
    [[nodiscard]] inline float lambert(const normalized3& normal, const normalized3& light_dir) noexcept
    {
        return std::max(0.0F, dot(normal, light_dir));
    }

    color RaymarchRenderer::get_diffuse_lighting(
        const vec3& surface_point, const normalized3& normal, size_t /*recursion_depth*/) const noexcept
    {
        //TODO: implement other types of lighting
        return get_lamp_lighting(surface_point, normal);
    }

    color RaymarchRenderer::get_lamp_lighting(const vec3& surface_point, const normalized3& normal) const noexcept
    {
        color res{};
        for (const auto& lamp : lamps_) {
            res += calculate_lamp_lighting(lamp, surface_point, normal);
        }
        return res;
    }

    color RaymarchRenderer::calculate_lamp_lighting(const ILamp_p& lamp, const vec3& surface_point, const normalized3& normal) const noexcept
    {
        const vec3 light_vector = lamp->get_light_vector(surface_point);
        const auto light_dist = mag(light_vector);
        const vec3 light_dir = light_vector / light_dist;

        if(lambert(normal, light_dir) > 0.0F && !raymarch(surface_point, light_dir, light_dist, nullptr, nullptr)) {
            return lamp->get_lighting(surface_point) * lambert(normal, light_dir);
        }

        return color{};
    }

#pragma endregion

} // namespace Raychel
