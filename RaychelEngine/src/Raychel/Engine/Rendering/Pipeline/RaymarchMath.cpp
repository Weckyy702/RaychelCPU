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

#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Engine/Objects/Interface.h"

namespace Raychel {

    vec3 RaymarchRenderer::_getRayDirectionFromUV(const vec2& uv) const noexcept
    {
        return normalize(   (cam_data_.forward*cam_data_.zoom) +
                            (cam_data_.right * uv.x) + 
                            (cam_data_.up * uv.y) );
    }

    

    RenderResult RaymarchRenderer::_raymarchFunction(const RaymarchData& req) const noexcept
    {
        const vec2 screenspace_uv = _getScreenspaceUV(req.uv);
        const vec3 origin = cam_data_.position;
        const vec3 direction = _getRayDirectionFromUV(req.uv);
    
        if(!failed_) {
            try {
                color res = getShadedColor(origin, direction, 0);
                return {screenspace_uv, res};
            
            }catch(const exception_context& exception) {
                new (&current_exception_) exception_context(exception);
                failed_ = true;
            }catch(...) {
                RAYCHEL_TERMINATE("RaymarchRenderer::getShadedColor() threw unexpected exception!");
            }
        }

        return {};
    }

    color RaymarchRenderer::getShadedColor(const vec3& origin, const vec3& direction, size_t recursion_depth) const
    {
        if(recursion_depth < raymarch_data_.max_recursion_depth){
            float depth = 0;
            if(raymarch(origin, direction, raymarch_data_.max_ray_depth, &depth, nullptr)){
                const RaymarchHitInfo hit_info = getHitInfo(origin, direction, depth);
                return hit_info.hit_object->getSurfaceColor(hit_info.shading_data, recursion_depth+1);
            }
        }
        return color{direction};
    }



    RaymarchHitInfo RaymarchRenderer::getHitInfo(const vec3& origin, const vec3& direction, float depth) const noexcept
    {
        const vec3 hit_point = origin + (direction * depth);

        const vec3 normal = getNormal(hit_point);
        const vec3 surface_point = hit_point + (normal * raymarch_data_.surface_bias);
        
        const IRaymarchable* hit_obj = getHitObject(hit_point);
        RAYCHEL_ASSERT(hit_obj);

        return {{surface_point, normal, direction, 0, depth}, hit_obj};
    }

    vec3 RaymarchRenderer::getNormal(const vec3& p) const noexcept
    {
        const float k = raymarch_data_.normal_bias;
        return normalize(vec3{
            sdScene(p+vec3{k, 0, 0}) - sdScene(p + vec3{-k, 0, 0}),
            sdScene(p+vec3{0, k, 0}) - sdScene(p + vec3{0, -k, 0}),
            sdScene(p+vec3{0, 0, k}) - sdScene(p + vec3{0, 0, -k}),
        });
    }

    IRaymarchable* RaymarchRenderer::getHitObject(const vec3& p) const noexcept
    {
        float min_distance = raymarch_data_.max_ray_depth;
        IRaymarchable* closest_object = nullptr;
        for(const auto& object : *objects_) {
            float object_distance = object->eval(p);

            if(object_distance < raymarch_data_.distance_bias && std::abs(object_distance) < min_distance) {
                min_distance = std::abs(object_distance);
                closest_object = object;
            }

        }
        return closest_object;
    }



    float RaymarchRenderer::sdScene(const vec3& p) const
    {
        float min = 10.0;
        for(const auto obj : *objects_) {
            min = std::min(min, obj->eval(p));
        }
        return min;
    }

    

    bool RaymarchRenderer::raymarch(const vec3& origin, const vec3& direction, float max_depth, float* out_depth, size_t* out_num_ray_steps) const noexcept
    {
        size_t i = 0;
        float depth = 0;
        while(depth < max_depth) {
            const vec3 p = origin + (depth*direction);

            const float scene_dist = sdScene(p);

            if(scene_dist < raymarch_data_.distance_bias) {
                if(out_depth)
                    *out_depth = depth;
                if(out_num_ray_steps)
                    *out_num_ray_steps = i;
                return true;
            }

            depth += scene_dist;
            i++;
        }
        return false;
    }

}