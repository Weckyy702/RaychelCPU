#include <algorithm>
#include <execution>
#include <functional>

#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Engine/Interface/Camera.h"

namespace Raychel {

#pragma region Setup functions

    void RaymarchRenderer::setRenderSize(const vec2i& new_size)
    {
        RAYCHEL_LOG("Setting render output size to ", new_size, " (aspect ratio of ", (static_cast<double>(new_size.x)/new_size.y), ")");
        output_size_ = new_size;
        _refillRequestBuffer();
    }

    void RaymarchRenderer::setSceneData(const not_null<std::vector<IRaymarchable_p>*> objects/*,
                                        const not_null<TextureProvider<color>*> background_texture*/)
    {
        objects_ = objects;
        // background_ = background_texture;
    }

    void RaymarchRenderer::_refillRequestBuffer()
    {
        
        RAYCHEL_LOG("Refilling request buffer...");

        requests_.clear();
        size_t request_count = output_size_.x * output_size_.y;
        requests_.reserve(request_count);

        double aspect_ratio = static_cast<double>(output_size_.x) / output_size_.y;

        for(auto i = 0; i < output_size_.y; i++) {
            for(auto j = 0; j < output_size_.x; j++) {
                auto idx = i * output_size_.y + j;
                requests_.push_back(_getRootRequest(j, i, aspect_ratio));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchRequest RaymarchRenderer::_getRootRequest(size_t x, size_t y, double ar) const
    {
        //generate UVs in range [-0.5; 0.5]

        double dx = ( static_cast<double>(x) / (output_size_.x-1) ) - 0.5;
        double dy = -( static_cast<double>(y) / (output_size_.y-1) ) + 0.5;

        //handle non-square aspect ratios
        if(ar > 1.0)
            dx *= ar;
        else
            dy /= ar;

        return {vec2{dx, dy}};
    }

#pragma endregion

#pragma region Render functions

    Texture<RenderResult> RaymarchRenderer::renderImage(const Camera& cam)
    {

        _setupCamData(cam);

        Texture<RenderResult> output{/*output_size_*/requests_.size()};

        _renderToTexture(output);

        return output;
    }

    void RaymarchRenderer::_renderToTexture(Texture<RenderResult>& output_texture) const
    {

        using namespace std::placeholders;
        static const auto f = [this](const RaymarchRequest& req){
            return _raymarchFunction(req);
        };

        RAYCHEL_LOG("Starting render...")

        std::transform(std::execution::par, requests_.cbegin(), requests_.cend(), output_texture.begin(), f);

        RAYCHEL_LOG("Finished render!");
    }

    void RaymarchRenderer::_setupCamData(const Camera& cam) noexcept
    {
        cam_data_.position = cam.transform_.position;
        cam_data_.forward = cam.forward();
        cam_data_.right = cam.right();
        cam_data_.up = cam.up();
        cam_data_.zoom = cam.zoom();

        RAYCHEL_LOG("Rendering with Camera at ", cam_data_.position, ", looking in direction: ", cam_data_.forward);
    }

    #pragma region Raymarch Functions

    vec3 RaymarchRenderer::_getRayDirectionFromUV(const vec2& uv) const noexcept
    {
        return normalize(   (cam_data_.forward*cam_data_.zoom) +
                            (cam_data_.right * uv.x) + 
                            (cam_data_.up * uv.y) );
    }

    RenderResult RaymarchRenderer::_raymarchFunction(const RaymarchRequest& req) const
    {
        double depth=0;
        const vec3 origin = cam_data_.position;
        vec3 direction = _getRayDirectionFromUV(req.uv);

        if(raymarch(origin, direction, 10, &depth))
            return {req.uv, color{1-(depth/10.0)}};
        return {req.uv, color{direction}};
    }

    double RaymarchRenderer::sdScene(const vec3& p) const
    {
        double min = 10.0;
        for(const auto obj : *objects_) {
            min = std::min(min, obj->eval(p));
        }
        return min;
    }

    bool RaymarchRenderer::raymarch(const vec3& origin, const vec3& direction, double max_depth, double* out_depth) const noexcept
    {
        double depth = 0;
        while(depth < max_depth) {
            const vec3 p = origin + (depth*direction);

            const double scene_dist = sdScene(p);

            if(scene_dist < 0.001) {
                if(out_depth)
                    *out_depth = depth;
                return true;
            }

            depth += scene_dist;
        }
        return false;
    }

    #pragma endregion

#pragma endregion

}