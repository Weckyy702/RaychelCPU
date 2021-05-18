/**
*\file CubeTexture.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for CubeTexture class
*\date 2021-04-21
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
#ifndef RAYCHEL_CUBE_TEXTURE_H
#define RAYCHEL_CUBE_TEXTURE_H

#include "Raychel/Core/utils.h"
#include "TextureType.h"
#include "TextureProvider.h"
    
namespace Raychel {

    /**
    *\brief Wrapper around a Cube Map or a procedural Texture
    *
    *\tparam T Value type stored in the Cube Map
    */
    template<typename T>
    class CubeTexture
    {
        using value_type_ = std::remove_cv_t<std::remove_reference_t<T>>;
        using sample_func = std::function<value_type_(const vec3&)>;
        using provider_list = std::array<TextureProvider<value_type_>, 6>;
    
    public:
        using value_type = value_type_;

        CubeTexture()
            :type_{TextureType::constant}, constant_{}
        {}

        CubeTexture(const sample_func& func)
            :type_{TextureType::function}, func_{func}
        {}

        CubeTexture(const provider_list& providers)
            :type_{TextureType::image}, providers_{providers}
        {}

        CubeTexture(const value_type& constant)
            :type_{TextureType::constant}, constant_{constant}
        {}

        CubeTexture(const CubeTexture& rhs)
            :type_{rhs.type_}
        {
            switch (type_)
            {
            case TextureType::function:
                new(&func_) sample_func{rhs.func_};
                break;
            case TextureType::image:
                new(&providers_) provider_list{rhs.providers_};
                break;
            case TextureType::constant:
                new(&constant_) value_type{rhs.constant_};
                break;
            default:
                RAYCHEL_ASSERT_NOT_REACHED;
            }
        }

        CubeTexture(CubeTexture&& rhs) noexcept
            :type_{rhs.type_}
        {
            switch (type_)
            {
            case TextureType::function:
                new(&func_) sample_func{std::move(rhs.func_)};
                break;
            case TextureType::image:
                new(&providers_) provider_list{std::move(rhs.providers_)};
                break;
            case TextureType::constant:
                new(&constant_) value_type{std::move(rhs.constant_)};
                break;
            default:
                RAYCHEL_ASSERT_NOT_REACHED;
            }
        }

        CubeTexture& operator=(const CubeTexture& rhs) noexcept
        {
            _destroyActiveMember();

            type_ = rhs.type_;
            switch (type_)
            {
            case TextureType::function:
                new(&func_) sample_func{rhs.func_};
                break;
            case TextureType::image:
                new(&providers_) provider_list{rhs.providers_};
                break;
            case TextureType::constant:
                new(&constant_) value_type{rhs.constant_};
                break;
            default:
                RAYCHEL_ASSERT_NOT_REACHED;
            }
            return *this;
        }

        CubeTexture& operator=(CubeTexture&& rhs) noexcept
        {
            _destroyActiveMember();

            type_ = rhs.type_;
            switch (type_)
            {
            case TextureType::function:
                new(&func_) sample_func{std::move(rhs.func_)};
                break;
            case TextureType::image:
                new(&providers_) provider_list{std::move(rhs.providers_)};
                break;
            case TextureType::constant:
                new(&constant_) value_type{std::move(rhs.constant_)};
                break;
            default:
                RAYCHEL_ASSERT_NOT_REACHED;
            }

            return *this;
        }

        /**
        *\brief Evaluate the Cube Map for the given direction
        *
        *\param dir direction to evaluate. Must be normalized
        *\return value_type 
        */
        value_type operator()(const normalized3& dir) const
        {
            RAYCHEL_ASSERT_NORMALIZED(dir);

            switch(type_) {
                case TextureType::function:
                    RAYCHEL_ASSERT(func_);
                    return func_(dir);
                case TextureType::image:
                    return _evaluate_cube_map(dir);
                case TextureType::constant:
                    return constant_;
            }
            RAYCHEL_ASSERT_NOT_REACHED;
        }

        ~CubeTexture() noexcept {
            _destroyActiveMember();
        }

    private:

        void _destroyActiveMember() noexcept
        {
            switch(type_) {
                case TextureType::function:
                    func_.~sample_func();
                break;
                case TextureType::image:
                    providers_.~provider_list();
                break;
                case TextureType::constant:
                    constant_.~value_type();
                break;
            }
        }

        value_type _evaluate_cube_map(const normalized3& dir) const
        {
            RAYCHEL_ASSERT_NORMALIZED(dir);
            //TODO: implement
            return value_type{};
        }


        TextureType type_;

        /**
        *\brief Space-saving wrapper for CubeTexture members
        *
        */
        union {
            sample_func func_;
            provider_list providers_;
            value_type constant_;
        };
    };
    

}

#endif //!RAYCHEL_CUBE_TEXTURE_H