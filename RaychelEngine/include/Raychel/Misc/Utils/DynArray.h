/**
* \file DynArray.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Dynamically allocated static array
* \date 2021-07-07
* 
* MIT License
* Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
*/
#ifndef RAYCHEL_DYN_ARRAY_H
#define RAYCHEL_DYN_ARRAY_H

#include <memory>
#include "Raychel/Core/Raychel_assert.h"

namespace Raychel {

    template <typename T>
    class DynArray
    {
    public:
        using value_type = std::remove_reference_t<std::remove_cv_t<T>>;

        explicit DynArray(std::size_t size) noexcept : size_{size}, arr_{new value_type[size]}
        {
            RAYCHEL_ASSERT(arr_ != nullptr);
            if constexpr (std::is_default_constructible_v<value_type>) {
                std::uninitialized_default_construct_n(arr_, size_);
            }
        }

        DynArray(const DynArray& other) noexcept : DynArray{other.size_}
        {
            RAYCHEL_ASSERT(other.arr_ != nullptr);
            std::uninitialized_copy_n(other.arr_, other.size_, arr_);
        }

        DynArray(DynArray&& other) noexcept : size_{other.size_}, arr_{other.arr_}
        {
            RAYCHEL_ASSERT(arr_ != nullptr);
            other.reset_();
        }

        DynArray& operator=(const DynArray& other)
        {
            if (this == &other) {
                return *this;
            }

            clear_();

            size_ = other.size_;
            arr_ = new value_type[size_];
            RAYCHEL_ASSERT(arr_ != nullptr);

            std::uninitialized_copy_n(other.arr_, other.size_, arr_);

            return *this;
        }

        DynArray& operator=(DynArray&& other) noexcept
        {
            if (this == &other) {
                return *this;
            }

            clear_();

            size_ = other.size_;
            arr_ = other.arr_;
            RAYCHEL_ASSERT(arr_ != nullptr);

            other.reset_();

            return *this;
        }

        [[nodiscard]] std::size_t size() const noexcept
        {
            return size_;
        }

        [[nodiscard]] value_type& at(std::size_t idx) noexcept
        {
            RAYCHEL_ASSERT(idx < size_);
            return arr_[idx];
        }

        [[nodiscard]] const value_type& at(std::size_t idx) const noexcept
        {
            RAYCHEL_ASSERT(idx < size_);
            return arr_[idx];
        }

        [[nodiscard]] value_type& operator[](std::size_t idx) noexcept
        {
            return at(idx);
        }

        [[nodiscard]] const value_type& operator[](std::size_t idx) const noexcept
        {
            return at(idx);
        }

        [[nodiscard]] value_type* begin() const noexcept
        {
            return arr_;
        }

        [[nodiscard]] value_type* end() const noexcept
        {
            return arr_ + size_;
        }

        ~DynArray() noexcept
        {
            clear_();
        }

    private:
        void clear_() noexcept
        {
            delete[] arr_;
            reset_();
        }

        void reset_() noexcept
        {
            size_ = 0;
            arr_ = nullptr;
        }

        std::size_t size_;
        value_type* arr_;
    };
} // namespace Raychel

#endif //!RAYCHEL_DYN_ARRAY_H