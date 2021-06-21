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
#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {

    /**
    *\brief Unique owner for Objects, a camera and a background texture
    *
    */
    class Scene
    {

    public:
        Scene() = default;

        RAYCHEL_MAKE_NONCOPY(Scene);
        RAYCHEL_MAKE_DEFAULT_MOVE(Scene);

        template <typename T, typename... Args>
        void addObject(Args&&... args)
        {
            static_assert(
                std::is_base_of_v<IRaymarchable, T>,
                "Only Objects that derive from Raychel::IRaymarchable can be added to a scene!");
            static_assert(
                std::is_constructible_v<T, Args...>,
                "Raychel::Scene::addObject<T, Args...> requires T to be constructible from Args...!");

            objects_.push_back(new T(std::forward<Args>(args)...));
        }

        /**
        *\brief Set the Background texture for the scene
        *
        *\param texture new background texture
        *\return CubeTexture<color>& reference to the set texture
        */
       RAYCHEL_EXPORT  CubeTexture<color>& setBackgroundTexture(const CubeTexture<color>& texture);

        /**
        *\brief Set the Camera for the scene
        *
        *\param cam new camera
        *\return Camera& reference to the set camera
        */
        RAYCHEL_EXPORT Camera& setCamera(const Camera& cam);

        ~Scene()
        {
            //TODO: turn IRaymarchable_p into a smart pointer
            for (IRaymarchable_p ptr : objects_) {
                delete ptr;
            }
        }

        friend class RenderController;

    private:
        Camera cam_;
        CubeTexture<color> background_texture_;
        std::vector<IRaymarchable_p> objects_{};
        //TODO: implement
        //std::vector<Camera> cams_;
    };

} // namespace Raychel

#endif //RAYCHEL_SCENE_H