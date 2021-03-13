#ifndef RAYCHEL_SCENE_H
#define RAYCHEL_SCENE_H

#include "Raychel/Core/utils.h"
#include "Raychel/Engine/Objects/Interface.h"

namespace Raychel {


    //Container for objects and materials
    class Scene {

        public:

            Scene()=default;

            template<typename T>
            void addObject(T&& obj)
            {
                static_assert(std::is_base_of_v<IRaymarchable, T>, "Only Objects that derivs from Raychel::IRaymarchable can be added to a scene!");
                objects.push_back(new T(std::forward<T>(obj)));
            }

            Scene(const Scene&)=delete;
            Scene& operator=(const Scene&)=delete;

            ~Scene()
            {
                for(auto ptr : objects) {
                    delete ptr;
                }
                //delete the materials
            }

        friend class RenderController;

        private:
            std::vector<IRaymarchable*> objects;
            //std::vector<IMaterial*> materials;
    };

}

#endif //RAYCHEL_SCENE_H