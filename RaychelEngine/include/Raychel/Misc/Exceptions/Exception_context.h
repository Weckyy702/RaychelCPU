/**
*\file Exception_context.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for the exeption context struct
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
#ifndef RAYCHEL_EXCEPTION_CONTEXT_H
#define RAYCHEL_EXCEPTION_CONTEXT_H

#include "Raychel/Core/utils.h"

#define RAYCHEL_THROW_EXCEPTION(msg, fatal)                                                                                      \
    {                                                                                                                            \
        _register_render_exception(RAYCHEL_FUNC_NAME, msg, fatal);                                                               \
    }

namespace Raychel {

    /**
    *\brief Base class for all Exceptions in Raychel. Contains additional information compared to std::exception
    */
    class exception_context
    {

    public:

        exception_context()=default;

        exception_context(gsl::czstring<> what, gsl::czstring<> origin, bool fatal) noexcept
            : what_{what}, origin_{origin}, fatal_{fatal}
        {}

        [[nodiscard]] gsl::czstring<> what() const noexcept
        {
            return what_;
        }

        [[nodiscard]] gsl::czstring<> origin() const noexcept
        {
            return origin_;
        }

        [[nodiscard]] bool fatal() const noexcept
        {
            return fatal_;
        }

    private:
        gsl::czstring<> what_{""};
        gsl::czstring<> origin_{""};
        bool fatal_{false};
    };

} // namespace Raychel

#endif //!RAYCHEL_EXCEPTION_CONTEXT_H