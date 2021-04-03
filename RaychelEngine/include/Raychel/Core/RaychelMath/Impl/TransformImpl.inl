/**
*\file TransformImpl.inl
*\author weckyy702 (weckyy702@gmail.com)
*\brief Implementation for Transforms
*\date 2021-03-23
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
#include "../Transform.h"

namespace Raychel {

    template<typename T>
    auto TransformImp<T>::apply(const vec3& p) const -> vec3
    {
        return (position - p) * rotation;
    }

    template<typename T>
    template<typename To>
    TransformImp<To> TransformImp<T>::to() const noexcept
    {
        using vt = typename TransformImp<To>::value_type;
        static_assert(std::is_convertible_v<value_type, vt>, "Raychel::TransformImp<T>::to<To>() requires T to be convertible to To!");

        //wtf. Why is it like that???
        vec3Imp<vt> v = position.template to<vt>();
        QuaternionImp<vt> q = rotation.template to<vt>();
        
        return { v, q };
    }

}