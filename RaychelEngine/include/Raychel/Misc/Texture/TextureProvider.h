/*DONT FORGET THE COPYRIGHT ;)*/
#ifndef RAYCHEL_TEXTURE_PROVIDER_H
#define RAYCHEL_TEXTURE_PROVIDER_H

#include <functional>
#include <variant>

#include "Raychel/Core/Types.h"
#include "Raychel/Core/utils.h"
#include "Texture.h"
#include "TextureType.h"

namespace Raychel {

    template <typename T>
    class TextureProvider
    {

        using value_type_ = std::remove_cv_t<std::remove_reference_t<T>>;
        using sample_func = std::function<value_type_(const vec3&, const vec3&)>;
        using texture_t = Texture<value_type_>;

    public:
        using value_type = value_type_;

        TextureProvider() : constant_{}
        {}

        //NOLINTNEXTLINE: these constructors are supposed to be implicit
        /*implicit*/ TextureProvider(const sample_func& sample_function) : type_(TextureType::function), func_{sample_function}
        {}

        //NOLINTNEXTLINE: these constructors are supposed to be implicit
        /*implicit*/ TextureProvider(const texture_t& texture) : type_(TextureType::image), texture_{texture}
        {}

        //NOLINTNEXTLINE: these constructors are supposed to be implicit
        /*implicit*/ TextureProvider(const value_type& constant) : constant_{constant}
        {}

        TextureProvider(const TextureProvider& rhs) : type_{rhs.type_}
        {
            switch (type_) {
                case TextureType::function:
                    new (&func_) sample_func{rhs.func_};
                    break;
                case TextureType::image:
                    new (&texture_) texture_t{rhs.texture_};
                    break;
                case TextureType::constant:
                    new (&constant_) value_type{rhs.constant_};
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
            }
        }

        TextureProvider(TextureProvider&& rhs) noexcept : type_{rhs.type_}
        {
            switch (type_) {
                case TextureType::function:
                    new (&func_) sample_func{std::move(rhs.func_)};
                    break;
                case TextureType::image:
                    new (&texture_) texture_t{std::move(rhs.texture_)};
                    break;
                case TextureType::constant:
                    new (&constant_) value_type{std::move(rhs.constant_)};
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
            }
        }

        TextureProvider& operator=(const TextureProvider& rhs) noexcept
        {
            _destroy_active_member();

            type_ = rhs.type_;
            switch (type_) {
                case TextureType::function:
                    new (&func_) sample_func{rhs.func_};
                    break;
                case TextureType::image:
                    new (&texture_) texture_t{rhs.texture_};
                    break;
                case TextureType::constant:
                    new (&constant_) value_type{rhs.constant_};
                    break;
                default:
                    RAYCHEL_ASSERT_NOT_REACHED;
            }
            return *this;
        }

        TextureProvider& operator=(TextureProvider&& rhs) noexcept
        {
            _destroy_active_member();

            type_ = rhs.type_;
            switch (type_) {
                case TextureType::function:
                    new (&func_) sample_func{std::move(rhs.func_)};
                    break;
                case TextureType::image:
                    new (&texture_) texture_t{std::move(rhs.texture_)};
                    break;
                case TextureType::constant:
                    new (&constant_) value_type{std::move(rhs.constant_)};
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
            switch (type_) {
                case TextureType::function:
                    RAYCHEL_ASSERT(func_);
                    return func_(pos, normal);
                case TextureType::image:
                    return _get_value_from_texture(pos, normal);
                case TextureType::constant:
                    return constant_;
            }
            RAYCHEL_ASSERT_NOT_REACHED;
        }

        ~TextureProvider() noexcept
        {
            _destroy_active_member();
        }

    private:
        void _destroy_active_member() noexcept
        {
            switch (type_) {
                case TextureType::function:
                    func_.~sample_func();
                    break;
                case TextureType::image:
                    texture_.~texture_t();
                    break;
                case TextureType::constant:
                    constant_.~value_type();
                    break;
            }
        }

        [[nodiscard]] value_type _get_value_from_texture(const vec3& /*unused*/, const normalized3& /*unused*/) const
        {
            //TODO: implement
            return value_type{};
        }

        TextureType type_{TextureType::constant};

        /**
            *\brief Space-saving wrapper for CubeTexture members
            *
            */
        union
        {
            sample_func func_;
            texture_t texture_;
            value_type constant_;
        };
    };

} // namespace Raychel

#endif //!RAYCHEL_TEXTURE_PROVIDER_H