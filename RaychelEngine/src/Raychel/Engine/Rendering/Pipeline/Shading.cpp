#include <algorithm>
#include <execution>
#include <functional>

#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Rendering/Pipeline/Shading.h"
#include "Raychel/Engine/Interface/Camera.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {

#pragma region Setup functions

    void RaymarchRenderer::setRenderSize(const vec2i& new_size)
    {
        RAYCHEL_LOG("Setting render output size to ", new_size, " (aspect ratio of ", (static_cast<float>(new_size.x)/new_size.y), ")");
        output_size_ = new_size;
        _refillRequestBuffer();
    }

    void RaymarchRenderer::setSceneData(const not_null<std::vector<IRaymarchable_p>*> objects,
                                        const not_null<CubeTexture<color>*> background_texture)
    {
        objects_ = objects;
        background_texture_ = background_texture;

        set_scene_callback_renderer();
    }

    void RaymarchRenderer::set_scene_callback_renderer() {
        for(const auto& obj : *objects_) {
            obj->onRendererAttached(this);
        }
    }

    void RaymarchRenderer::_refillRequestBuffer()
    {
        RAYCHEL_LOG("Refilling request buffer to ", output_size_.x * output_size_.y, " pixels");

        requests_.clear();
        size_t request_count = output_size_.x * output_size_.y;
        requests_.reserve(request_count);

        aspect_ratio = static_cast<float>(output_size_.x) / output_size_.y;

        for(auto i = 0U; i < output_size_.y; i++) {
            for(auto j = 0U; j < output_size_.x; j++) {
                requests_.push_back(_getRootRequest(j, i));
            }
        }

        //in case window got smaller
        requests_.shrink_to_fit();
    }

    RaymarchData RaymarchRenderer::_getRootRequest(size_t x, size_t y) const
    {
        //generate UVs in range [-0.5; 0.5]

        float dx = ( static_cast<float>(x) / (output_size_.x) ) - 0.5F;
        float dy = ( static_cast<float>(y) / (output_size_.y) ) - 0.5F;

        //handle non-square aspect ratios
        if(aspect_ratio > 1.0)
            dx *= aspect_ratio;
        else
            dy /= aspect_ratio;

        return {vec2{dx, dy}};
    }

#pragma endregion

#pragma region Render functions

    std::optional<Texture<RenderResult>> RaymarchRenderer::renderImage(const Camera& cam)
    {
        _setupCamData(cam);

        Texture<RenderResult> output{output_size_};

        if(!_renderToTexture(output)){
            Logger::error("Image rendering failed with error: ", current_exception_.what() , "at (", current_exception_.origin(), ")!\n");
            //TODO: customizable error handling
            return std::nullopt;
        }

        return output;
    }

    bool RaymarchRenderer::_renderToTexture(Texture<RenderResult>& output_texture) const
    {

        using namespace std::placeholders;

        static const auto f = [this](const RaymarchData& req){
            return _raymarchFunction(req);
        };

        RAYCHEL_LOG("Starting render...");

        std::transform(std::execution::par, requests_.cbegin(), requests_.cend(), output_texture.begin(), f);

        RAYCHEL_LOG("Finished render!");
        return !failed_;
    }

    void RaymarchRenderer::_setupCamData(const Camera& cam) noexcept
    {
        cam_data_.position = cam.transform_.position;
        cam_data_.forward = cam.forward();
        cam_data_.right = cam.right();
        cam_data_.up = cam.up();
        cam_data_.zoom = cam.zoom();

        RAYCHEL_LOG("Rendering with Camera at ", cam_data_.position,
        ", with local coordinate frame: { +x: ", cam_data_.right, ", +y: ", cam_data_.up, ", +z: ", cam_data_.forward, " }");
    }

#pragma endregion

    vec2 RaymarchRenderer::_getScreenspaceUV(const vec2& uv) const noexcept
    {
        vec2 actual_uv = uv;
        
        if(aspect_ratio > 1.0) {
            actual_uv.x /= aspect_ratio;
        } else {
            actual_uv.y *= aspect_ratio;
        }

        actual_uv += vec2{0.5f, 0.5f};

        actual_uv.y = 1.0f - actual_uv.y;

        return actual_uv;
    }

}