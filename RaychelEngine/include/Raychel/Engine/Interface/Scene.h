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
#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Interface/Camera.h"
#include "Raychel/Misc/Texture/CubeTexture.h"

namespace Raychel {


    /**
    *\brief Unique owner for Objects, a camera and a background texture
    *
    */
    class Scene {

        public:

            Scene()=default;

            template<typename T>
            void addObject(T&& obj)
            {
                static_assert(std::is_base_of_v<IRaymarchable, T>, "Only Objects that derive from Raychel::IRaymarchable can be added to a scene!");
                objects_.push_back(new T(std::forward<T>(obj)));
            }

            Scene(const Scene&)=delete;
            Scene& operator=(const Scene&)=delete;

            ~Scene()
            {
                for(auto ptr : objects_) {
                    delete ptr;
                }
            }

        friend class RenderController;

        Camera cam;

        //private:
            std::vector<IRaymarchable_p> objects_;
            CubeTexture<color> background_texture_;
            //TODO: implement
            //std::vector<Camera> cams_;
    };

}

#endif //RAYCHEL_SCENE_H