#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Engine/Rendering/Pipeline/Tracing.h"
#include "Raychel/Engine/Interface/Scene.h"

namespace Raychel {

    vec2i RenderController::setOutputSize(const vec2i& new_size)
    {
        output_size_ = new_size;

        _refillRequestBuffer(new_size);

        return output_size_;
    }



    void RenderController::setCurrentScene(const not_null<Scene*> new_scene) 
    {
        current_scene_ = new_scene;
    }


    Texture<RenderResult> RenderController::getRenderedImage() const
    {
        const RaymarchController tracer{&current_scene_->objects};
        //const ShaderController shader{&current_scene_->materials};

        const auto hit_data = tracer.trace(requests_);

        /*

        keep tracing and shading over and over again until all rays have completed

        new_requests, output = shader.shade(hit_data);

        while(!shader.done) {

            res += output;

            hit_data = tracer.trace( objects );

            new_requests, output = shader.shade(hit_data)

        }
        
        return res;
        */

        auto t = Texture<RenderResult>{};
        t.reserve(hit_data.size());

        for(const auto& d : hit_data) {
            t.push_back({d.hit_normal});
        }

        return t;
    }


    void RenderController::_refillRequestBuffer(const vec2i& new_size)
    {
        
        RAYCHEL_LOG("Refilling request buffer\n");

        requests_.clear();
        size_t request_count = new_size.x * new_size.y;
        requests_.reserve(request_count);

        for(auto i = 0; i < new_size.y; i++) {
            for(auto j = 0; j < new_size.x; j++) {
                auto idx = i * new_size.y + j;

                RaymarchRequest req = _getRootRequest(j, i);

                requests_.push_back(std::move(req));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }



    RaymarchRequest RenderController::_getRootRequest(size_t x, size_t y) const
    {
        // const Camera& cam = current_scene_->cam;

        // vec3 origin = cam.transform.position;

        double dx = static_cast<double>(x) /  output_size_.x;
        double dy = static_cast<double>(y) / output_size_.y;

        //vec3 dir = (cam.forward() * cam.zoom()) + (cam.right() * dx) + (cam.up() * dy);

        vec3 origin = vec3{0, 1, 0};
        vec3 dir = vec3{dx, dy, 1};

        return {origin, dir};
    }

}