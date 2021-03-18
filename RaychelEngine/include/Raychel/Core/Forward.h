#ifndef RAYCHEL_FORWARD_H
#define RAYCHEL_FORWARD_H

#include <vector>

namespace Raychel {

    //Image Texture
    template<typename T>
    //class Texture; 
    using Texture = std::vector<T>;

    //Wrapper for either an Image or procedural Texture
    template<typename T>
    class TextureProvider;

    class Scene;

    struct Camera;

    struct IRaymarchable;

}

#endif //RAYCHEL_FORWARD_H