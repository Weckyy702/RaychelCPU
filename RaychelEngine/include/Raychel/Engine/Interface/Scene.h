/**
*\file Scene.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for Scene class
*\date 2021-03-25
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
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/
#ifndef RAYCHEL_SCENE_H
#define RAYCHEL_SCENE_H

#include "Raychel/Core/utils.h"
#include "Raychel/Engine/Interface/Camera.h"
#include "Raychel/Engine/Lights/Interface.h"
#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Rendering/Renderer.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {

    /**
    *\brief Unique owner for Objects, a camera and a background texture
    *
    */
    class Scene
    {

    public:
        RAYCHEL_EXPORT Scene();

        RAYCHEL_MAKE_NONCOPY(Scene);
        RAYCHEL_MAKE_DEFAULT_MOVE(Scene);

        /**
        *\brief Add a new object to the scene. Returns a reference to the newly created object
        *
        *\tparam T Type of object. Must derive from IRaymarchable
        *\tparam Args Constructor argument types for the object
        *\param args Constructor arguments for the object
        *\return IRaymarchable_p& reference to the newly created object
        */
        template <typename T, typename... Args>
        T& add_object(Args&&... args)
        {
            static_assert(
                std::is_base_of_v<IRaymarchable, T>,
                "Only Objects that derive from Raychel::IRaymarchable can be added to a scene!");
            static_assert(
                std::is_constructible_v<T, Args...>,
                "Raychel::Scene::add_object<T, Args...> requires T to be constructible from Args...!");

            objects_.emplace_back(new T(std::forward<Args>(args)...));
            _notify_renderer();

            return static_cast<T&>(*(objects_.back().get()));
        }

        /**
        *\brief Add a new lamp to the scene. Returns a reference to the newly created lamp
        *
        *\tparam T Type of lamp. Must derive from ILamp
        *\tparam Args Constructor argument types for the lamp
        *\param args Constructor arguments for the lamp
        *\return ILamp_p& reference to the newly created lamp
        */
        template <typename T, typename... Args>
        T& add_lamp(Args&&... args)
        {
            static_assert(std::is_base_of_v<ILamp, T>, "Only Objects that derive from Raychel::ILamp can be added as lamps!");
            static_assert(
                std::is_constructible_v<T, Args...>,
                "Raychel::Scene::add_lamp<T, Args...> requires T to be constructible from Args...!");

            lamps_.emplace_back(new T(std::forward<Args>(args)...));
            _notify_renderer();

            return static_cast<T&>(*(lamps_.back().get()));
        }

        /**
        *\brief Set the Background texture for the scene
        *
        *\param texture new background texture
        *\return CubeTexture<color>& reference to the set texture
        */
        RAYCHEL_EXPORT CubeTexture<color>& set_background_texture(const CubeTexture<color>& texture);

        /**
        *\brief Set the Camera for the scene
        *
        *\param cam new camera
        *\return Camera& reference to the set camera
        */
        RAYCHEL_EXPORT Camera& set_camera(const Camera& cam);

        /**
        *\brief Get the Renderer associated with this scene
        *
        *\return RAYCHEL_EXPORT 
        */
        RAYCHEL_EXPORT [[nodiscard]] RenderController& get_renderer() const;

        ~Scene() = default;
        friend class RenderController;

    private:
        void _notify_renderer() const noexcept;

        Camera cam_;
        std::unique_ptr<RenderController> renderer_;

        CubeTexture<color> background_texture_;
        std::vector<IRaymarchable_p> objects_{};
        std::vector<ILamp_p> lamps_{};
        //TODO: implement
        //std::vector<Camera> cams_;
    };

} // namespace Raychel

#endif //RAYCHEL_SCENE_H