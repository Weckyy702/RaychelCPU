/*DONT FORGET THE COPYRIGHT ;)*/
#ifndef RAYCHEL_TEXTURE_PROVIDER_H
#define RAYCHEL_TEXTURE_PROVIDER_H

#include <functional>
#include <variant>

#include "Raychel/Core/utils.h"
#include "Raychel/Core/Types.h"
#include "Texture.h"
#include "TextureType.h"
    
namespace Raychel {

    template<typename T>
    class TextureProvider {

        using value_type_ = std::remove_cv_t<std::remove_reference_t<T>>;
        using sample_func = std::function<value_type_(const vec3&, const vec3&)>;
        using texture_t = Texture<value_type_>;

        public:
            using value_type = value_type_;

            TextureProvider()
                :type_(TextureType::constant), constant_{}
            {}

            /*implicit*/TextureProvider(const sample_func& sample_function)
                :type_(TextureType::function), func_{sample_function}
            {}

            /*implicit*/TextureProvider(const texture_t& texture)
                :type_(TextureType::image), texture_{texture}
            {}

            /*implicit*/TextureProvider(const value_type& constant)
                :type_(TextureType::constant), constant_{constant}
            {}

            value_type operator()(const vec3& pos, const vec3& normal) const
            {
                switch(type_) {
                    case TextureType::function:
                        return func_(pos, normal);
                    case TextureType::image:
                        return _get_value_from_texture(pos, normal);
                    case TextureType::constant:
                        return constant_;
                }
                RAYCHEL_ASSERT_NOT_REACHED;
            }

        private:

            value_type _get_value_from_texture(const vec3&, const vec3&) const
            {
                //TODO: implement
                return T();
            }

            TextureType type_;
            sample_func func_;
            texture_t texture_;
            value_type constant_{};
    };

}

#endif //!RAYCHEL_TEXTURE_PROVIDER_H