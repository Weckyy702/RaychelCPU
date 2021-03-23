#ifndef RAYCHEL_SCENE_H
#define RAYCHEL_SCENE_H

#include "Raychel/Core/utils.h"
#include "Raychel/Engine/Objects/Interface.h"
#include "Raychel/Engine/Interface/Camera.h"

namespace Raychel {


    //Unique owner for objects, a camera and a background texture
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

        private:
            std::vector<IRaymarchable_p> objects_;

            //TODO: implement
            //TextureProvider<color> background_texture_;
            //Camera camera_;
    };

}

#endif //RAYCHEL_SCENE_H