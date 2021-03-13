#ifndef RAYCHEL_FORWARD_H
#define RAYCHEL_FORWARD_H

#include <vector>

namespace Raychel {

    template<typename T>
    //class Texture; 
    using Texture = std::vector<T>;

    class Scene;

    struct Camera;

    struct IRaymarchable;

}

#endif //RAYCHEL_FORWARD_H