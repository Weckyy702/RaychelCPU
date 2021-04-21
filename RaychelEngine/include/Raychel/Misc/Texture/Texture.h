/**
*\file Texture.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for image backed textures
*\date 2021-04-17
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
#ifndef RAYCHEL_TEXTURE_H
#define RAYCHEL_TEXTURE_H

#include <vector>

#include "Raychel/Core/utils.h"
#include "Raychel/Core/Types.h"

namespace Raychel
{
    /**
    *\brief An image texture of the specified pixel type. Supports uv indexing
    *
    *\tparam Pixel_t 
    */
    template<typename Pixel_t>
    class Texture {

        using value_type_ = std::remove_cv_t<std::remove_reference_t<Pixel_t>>;
        using iterator_ = typename std::vector<value_type_>::iterator;
        using const_iterator_ = typename std::vector<value_type_>::const_iterator;

    public:
        using value_type = value_type_;

        Texture()=default;

        explicit Texture(const vec2i& size)
            :size_(size), pixel_buffer_{size_.x*size_.y}
        {}

        /**
        *\brief sample the texture at the specified uv coordinate
        *
        *\return value_type& 
        */
        value_type& at(const vec2i&);
        value_type& at(const vec2&);

        const value_type& at(const vec2i&) const;
        const value_type& at(const vec2&) const;

        vec2i size() const {
            return size_;
        }

        iterator_ begin() {
            return pixel_buffer_.begin();
        }

        iterator_ end() {
            return pixel_buffer_.end();
        }

        const_iterator_ begin() const {
            return pixel_buffer_.cbegin();
        }

        const_iterator_ end() const {
            return pixel_buffer_.cend();
        }

    private:

        size_t vecToIndex(const vec2i& _uv) const noexcept {
            const vec2i uv = min(max(_uv, vec2i{0, 0}), size_); //clamp the vector
            return (uv.y * size_.x) + uv.x;
        }

        size_t vecToIndex(const vec2& _uv) const noexcept {
            const vec2 pixel_uv = _uv*(size_.to<number_t>());
            return vecToIndex(pixel_uv.to<size_t>());
        }

        vec2i size_;
        std::vector<value_type> pixel_buffer_;
    };

    template<typename T>
    auto Texture<T>::at(const vec2i& _uv) -> value_type&
    {
        return pixel_buffer_.at(vecToIndex(_uv));
    }

    template<typename T>
    auto Texture<T>::at(const vec2& _uv) -> value_type&
    {
        return pixel_buffer_.at(vecToIndex(_uv));
    }

    template<typename T>
    auto Texture<T>::at(const vec2i& _uv) const -> const value_type&
    {
        return pixel_buffer_.at(vecToIndex(_uv));
    }

    template<typename T>
    auto Texture<T>::at(const vec2& _uv) const -> const value_type&
    {
        return pixel_buffer_.at(vecToIndex(_uv));
    }

}



#endif //!RAYCHEL_TEXTURE_H