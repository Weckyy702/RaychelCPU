#include <algorithm>
#include <execution>

#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Logger.h"

namespace Raychel {

#pragma region Setup functions

    void RaymarchRenderer::setRenderSize(const vec2i& new_size)
    {
        RAYCHEL_LOG("Setting render output size to ", new_size, " (aspect ratio of ", (static_cast<double>(new_size.x)/new_size.y), ")");
        output_size_ = new_size;
        _refillRequestBuffer();
    }

    void RaymarchRenderer::setSceneData(const not_null<Camera*> cam,
                                        const not_null<std::vector<IRaymarchable_p>*> objects,
                                        const not_null<TextureProvider<color>*> background_texture)
    {
        objects_ = objects;
        cam_ = cam;
        background_ = background_texture;
    }

    void RaymarchRenderer::_refillRequestBuffer()
    {
        
        RAYCHEL_LOG("Refilling request buffer");

        requests_.clear();
        size_t request_count = output_size_.x * output_size_.y;
        requests_.reserve(request_count);

        for(auto i = 0; i < output_size_.y; i++) {
            for(auto j = 0; j < output_size_.x; j++) {
                auto idx = i * output_size_.y + j;
                requests_.push_back(_getRootRequest(j, i));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchRequest RaymarchRenderer::_getRootRequest(size_t x, size_t y) const
    {
        // vec3 origin = cam_.transform.position;

        //vec3 dir = (cam_.forward() * cam_.zoom()) + (cam_.right() * dx) + (cam_.up() * dy);

        //vec3 dir = (vec3{dx, dy, 0}) / (sq(dx) + sq(dy)); this produces some crazy stuff

        double ar = static_cast<double>(output_size_.x) / output_size_.y;

        double dx = ( static_cast<double>(x) / (output_size_.x-1) ) - 0.5;
        double dy = - ( static_cast<double>(y) / (output_size_.y-1) ) + 0.5;

        if(ar > 1.0)
            dx *= ar;
        else
            dy /= ar;

        vec3 origin = vec3{0, 0, 0};
        vec3 dir = normalize(vec3{dx, dy, 1});

        return {origin, dir};
    }

#pragma endregion

#pragma region Render functions

    Texture<RenderResult> RaymarchRenderer::renderImage() const
    {
        Texture<RenderResult> output{/*output_size_*/requests_.size()};

        _renderToTexture(output);

        return output;
    }

    void RaymarchRenderer::_renderToTexture(Texture<RenderResult>& output_texture) const
    {
        std::transform(std::execution::par_unseq, requests_.cbegin(), requests_.cend(), output_texture.begin(),
        [this](const RaymarchRequest& req) -> RenderResult
        {
            return {color{req.direction}};
        });
    }

#pragma endregion

}