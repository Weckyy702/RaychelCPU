/**
*\file Raychel_assert.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for assertion macros
*\date 2021-06-15
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
#ifndef RAYCHEL_ASSERT_H
#define RAYCHEL_ASSERT_H

#include "Logger.h"
#include "compat.h"

#define RAYCHEL_STRINGIFY_IMPL(x) #x

#define RAYCHEL_STRINGIFY(x) RAYCHEL_STRINGIFY_IMPL(x)

//terminate the application with the provided message
#define RAYCHEL_TERMINATE(...)                                                                                                   \
    Logger::fatal(RAYCHEL_FUNC_NAME, " at (", __FILE__, ":", __LINE__, "): ", __VA_ARGS__, '\n');                                \
    std::terminate();

#if defined(RAYCHEL_DEBUG) || !defined(NDEBUG)
    #define RAYCHEL_ASSERT(exp)                                                                                                  \
        if (!(exp)) {                                                                                                            \
            RAYCHEL_TERMINATE("Assertion '", RAYCHEL_STRINGIFY(exp), "' failed!");                                               \
        }
#else
    #define RAYCHEL_ASSERT(exp) Expects(exp)
#endif

#define RAYCHEL_ASSERT_NOT_REACHED RAYCHEL_TERMINATE("Assertion failed! Expected to not execute ", __FILE__, ":", __LINE__)

#define RAYCHEL_ASSERT_NORMALIZED(vec) RAYCHEL_ASSERT(equivalent(magSq(vec), 1.0f));

#endif //!RAYCHEL_ASSERT_H