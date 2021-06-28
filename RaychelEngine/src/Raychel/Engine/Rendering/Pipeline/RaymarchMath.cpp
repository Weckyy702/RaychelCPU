/**
*\file RaymarchMath.cpp
*\author weckyy702 (weckyy702@gmail.com)
*\brief Definitions for common raymarching math functions found in Shading.h
*\date 2021-04-13
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,#
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/

#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {

    vec3 RaymarchRenderer::_get_ray_direction_from_UV(const vec2& uv) const noexcept
    {
        return normalize((cam_data_.forward * cam_data_.zoom) + (cam_data_.right * uv.x) + (cam_data_.up * uv.y));
    }

    RenderResult RaymarchRenderer::_raymarch_function(const RaymarchData& req) const noexcept
    {
        const vec2 screenspace_uv = _get_screenspace_UV(req.uv);
        const vec3 origin = cam_data_.position;
        const vec3 direction = _get_ray_direction_from_UV(req.uv);

        if (!failed_) {
            try {
                color res = get_shaded_color(origin, direction, 0);
                return {screenspace_uv, res};

            } catch (const exception_context& exception) {
                new (&current_exception_) exception_context(exception);
                failed_ = true;
            } catch (...) {
                RAYCHEL_TERMINATE("RaymarchRenderer::getShadedColor() threw unexpected exception!");
            }
        }

        return {screenspace_uv, color{0}};
    }

    color RaymarchRenderer::get_shaded_color(const vec3& origin, const normalized3& direction, size_t recursion_depth) const
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);

        if (recursion_depth <= options_.max_recursion_depth) {
            float depth = 0;
            size_t num_ray_steps = 0;
            if (raymarch(origin, direction, options_.max_ray_depth, &depth, &num_ray_steps)) {
                const RaymarchHitInfo hit_info = get_hit_info(origin, direction, depth, num_ray_steps, recursion_depth);

                return hit_info.hit_object->getSurfaceColor(hit_info.shading_data);
            }
        }
        return background_texture_(direction);
    }

    RaymarchHitInfo RaymarchRenderer::get_hit_info(
        const vec3& origin, const normalized3& direction, float depth, size_t num_ray_steps,
        size_t recursion_depth) const noexcept
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);

        const vec3 hit_point = origin + (direction * depth);

        const vec3 normal = get_normal(hit_point);
        const vec3 surface_point = hit_point + (normal * options_.surface_bias);

        const IRaymarchable* hit_obj = get_hit_object(hit_point);
        RAYCHEL_ASSERT(hit_obj);

        return {PrimaryShadingData{{surface_point, normal, direction, recursion_depth + 1}, num_ray_steps, depth}, hit_obj};
    }

    vec3 RaymarchRenderer::get_normal(const vec3& p) const noexcept
    {
        const float k = options_.normal_bias;
        return normalize(vec3{
            sd_scene(p + vec3{k, 0, 0}) - sd_scene(p + vec3{-k, 0, 0}),
            sd_scene(p + vec3{0, k, 0}) - sd_scene(p + vec3{0, -k, 0}),
            sd_scene(p + vec3{0, 0, k}) - sd_scene(p + vec3{0, 0, -k}),
        });
    }

    IRaymarchable* RaymarchRenderer::get_hit_object(const vec3& p) const noexcept
    {
        float min_distance = options_.max_ray_depth;
        IRaymarchable* closest_object = nullptr;

        for (const auto& object : objects_) {
            float object_distance = object->eval(p);

            if (object_distance < options_.distance_bias && std::abs(object_distance) < min_distance) {
                min_distance = std::abs(object_distance);
                closest_object = object;
            }
        }

        return closest_object;
    }

    float RaymarchRenderer::sd_scene(const vec3& p) const
    {
        float min = 10.0;
        for (const auto& obj : objects_) {
            min = std::min(min, obj->eval(p));
        }
        return min;
    }

    bool RaymarchRenderer::raymarch(
        const vec3& origin, const normalized3& direction, float max_depth, float* out_depth,
        size_t* out_num_ray_steps) const noexcept
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);

        size_t i = 0;
        float depth = 0;
        while (depth < max_depth) {
            const vec3 p = origin + (depth * direction);

            const float scene_dist = sd_scene(p);

            if (scene_dist < options_.distance_bias) {
                if (out_depth != nullptr) {
                    *out_depth = depth;
                }
                if (out_num_ray_steps != nullptr) {
                    *out_num_ray_steps = i;
                }
                return true;
            }

            depth += scene_dist;
            i++;
        }
        return false;
    }

} // namespace Raychel