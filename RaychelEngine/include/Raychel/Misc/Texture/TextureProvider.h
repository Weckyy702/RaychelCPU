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
                :type_(TextureType::constant), values_{}
            {}

            /*implicit*/TextureProvider(const sample_func& sample_function)
                :type_(TextureType::function), values_{sample_function}
            {}

            /*implicit*/TextureProvider(const texture_t& texture)
                :type_(TextureType::image), values_{texture}
            {}

            /*implicit*/TextureProvider(const value_type& constant)
                :type_(TextureType::constant), values_{constant}
            {}

            TextureProvider(const TextureProvider& rhs)
                :type_{rhs.type_}
            {
                switch (type_)
                {
                case TextureType::function:
                    values_.func = rhs.values_.func;
                    break;
                case TextureType::image:
                    values_.texture = rhs.values_.texture;
                    break;
                case TextureType::constant:
                    values_.constant = rhs.values_.constant;
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
                }
            }

            TextureProvider(TextureProvider&& rhs)
                :type_{rhs.type_}
            {
                switch (type_)
                {
                case TextureType::function:
                    values_.func = std::move(rhs.values_.func);
                    break;
                case TextureType::image:
                    values_.texture = std::move(rhs.values_.texture);
                    break;
                case TextureType::constant:
                    values_.constant = std::move(rhs.values_.constant);
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
                }
            }

            TextureProvider& operator=(const TextureProvider& rhs) noexcept
            {
                type_ = rhs.type_;
                switch (type_)
                {
                case TextureType::function:
                    values_.func = rhs.values_.func;
                    break;
                case TextureType::image:
                    values_.texture = rhs.values_.texture;
                    break;
                case TextureType::constant:
                    values_.constant = rhs.values_.constant;
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
                }
                return *this;
            }

            TextureProvider& operator=(TextureProvider&& rhs) noexcept
            {
                type_ = rhs.type_;
                switch (type_)
                {
                case TextureType::function:
                    values_.func = std::move(rhs.values_.func);
                    break;
                case TextureType::image:
                    values_.texture = std::move(rhs.values_.texture);
                    break;
                case TextureType::constant:
                    values_.constant = std::move(rhs.values_.constant);
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
                }
                return *this;
            }

            /**
            *\brief Evaluate the Texture at the given position with the given normal
            *
            *\param pos position in the texture space
            *\param normal normal used for uv calculation
            *\return value_type 
            */
            value_type operator()(const vec3& pos, const vec3& normal) const
            {
                switch(type_) {
                    case TextureType::function:
                        return values_.func(pos, normal);
                    case TextureType::image:
                        return _get_value_from_texture(pos, normal);
                    case TextureType::constant:
                        return values_.constant;
                }
                RAYCHEL_ASSERT_NOT_REACHED;
            }

        private:

            value_type _get_value_from_texture(const vec3&, const vec3&) const
            {
                //TODO: implement
                return T();
            }

            /**
            *\brief Space saving wrapper for TextureProvider members
            *
            */
            union TextureValues
            {
                TextureValues()
                    :constant{}
                {}

                TextureValues(const sample_func& _func)
                    :func{_func}
                {}

                TextureValues(const texture_t& _texture)
                    :texture{_texture}
                {}

                TextureValues(const value_type& _constant)
                    :constant{_constant}
                {}

                ~TextureValues(){}

                sample_func func;
                texture_t texture;
                value_type constant;
            };
            

            TextureType type_;
            TextureValues values_;
    };

}

#endif //!RAYCHEL_TEXTURE_PROVIDER_H