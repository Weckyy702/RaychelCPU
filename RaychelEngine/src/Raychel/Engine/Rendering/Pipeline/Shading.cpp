#include <algorithm>
#include <execution>

#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Logger.h"

namespace Raychel {

#pragma region Setup functions

    void RaymarchRenderer::setRenderSize(const vec2i& new_size)
    {
        RAYCHEL_LOG("Refilling requests Buffer to ", new_size);
        _refillRequestBuffer(new_size);
    }

    void RaymarchRenderer::_refillRequestBuffer(const vec2i& new_size)
    {
        
        RAYCHEL_LOG("Refilling request buffer\n");

        requests_.clear();
        size_t request_count = new_size.x * new_size.y;
        requests_.reserve(request_count);

        for(auto i = 0; i < new_size.y; i++) {
            for(auto j = 0; j < new_size.x; j++) {
                auto idx = i * new_size.y + j;
                requests_.push_back(_getRootRequest(new_size, j, i));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchRequest RaymarchRenderer::_getRootRequest(const vec2i& output_size, size_t x, size_t y) const
    {
        // vec3 origin = cam_.transform.position;

        //vec3 dir = (cam_.forward() * cam_.zoom()) + (cam_.right() * dx) + (cam_.up() * dy);

        double dx = static_cast<double>(x) /  output_size.x;
        double dy = static_cast<double>(y) / output_size.y;

        vec3 origin = vec3{0, 1, 0};
        vec3 dir = vec3{dx, dy, 1};

        return {origin, dir};
    }

#pragma endregion

#pragma region Render functions

    Texture<RenderResult> RaymarchRenderer::renderImage() const
    {
        Texture<RenderResult> output{requests_.size()};

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