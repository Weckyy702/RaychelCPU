#include <algorithm>
#include <execution>

#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Logger.h"

namespace Raychel {

    Texture<RenderResult> RaymarchRenderer::renderImage(const vec2i& window_size, const Camera& cam) const
    {



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

                RaymarchRequest req = _getRootRequest(new_size, j, i);

                requests_.push_back(std::move(req));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchRequest RaymarchRenderer::_getRootRequest(const vec2i& output_size, size_t x, size_t y) const
    {
        // const Camera& cam = current_scene_->cam;

        // vec3 origin = cam.transform.position;

        double dx = static_cast<double>(x) /  output_size.x;
        double dy = static_cast<double>(y) / output_size.y;

        //vec3 dir = (cam.forward() * cam.zoom()) + (cam.right() * dx) + (cam.up() * dy);

        vec3 origin = vec3{0, 1, 0};
        vec3 dir = vec3{dx, dy, 1};

        return {origin, dir};
    }

}