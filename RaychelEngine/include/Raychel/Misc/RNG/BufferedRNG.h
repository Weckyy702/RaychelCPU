/**
* \file random.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Main include for Raychel random library
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
#ifndef RAYCHEL_BUFFERED_RNG_H
#define RAYCHEL_BUFFERED_RNG_H

#include "Raychel/Misc/Utils/DynArray.h"
#include <random>

namespace Raychel {

    template<typename T>
    class BufferedRNG {
    public:
        using value_type = std::remove_reference_t<std::remove_cv_t<T>>;
        static_assert(std::is_floating_point_v<value_type> || std::is_integral_v<value_type>, "Raychel::BufferedRNG<T> requires T to be of integral or floating-point type!");


        explicit BufferedRNG(std::size_t buffer_size)
            :buffer_{buffer_size}
        {
            refill_buffer_();
        }

        value_type operator()() const noexcept
        {
            static thread_local std::size_t buffer_idx=0U;

            buffer_idx = (buffer_idx + 1) % buffer_.size();

            return buffer_[buffer_idx];
        }

        private:

            void refill_buffer_() noexcept
            {
                std::random_device rd{};
                std::ranlux48 rng{rd()};
                
                if constexpr(std::is_floating_point_v<value_type>){
                    std::uniform_real_distribution<value_type> distr{0, 1};
                    refill_buffer_(rng, distr);
                    return;
                } else {
                    std::uniform_int_distribution<value_type> distr{-5, 5};
                    refill_buffer_(rng, distr);
                }
            }

            template<typename RNG, typename Distribution>
            void refill_buffer_(RNG& rng, Distribution distr) noexcept
            {
                for(std::size_t i = 0; i < buffer_.size(); i++) {
                    buffer_[i] = distr(rng);
                }
            }

            DynArray<T> buffer_;
    };

} // namespace Raychel

#endif //!RAYCHEL_BUFFERED_RNG_H