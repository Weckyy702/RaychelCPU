/**
*\file compat.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Compatibility defines
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
#ifndef RAYCHEL_COMPAT_H
#define RAYCHEL_COMPAT_H

#define RAYCHEL_OS_LINUX 0
#define RAYCHEL_OS_WIN32 1
#define RAYCHEL_OS_DARWIN 2 //Raychel isn't tested on MacOS!

#if !((defined(__cplusplus) && __cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L))
    #error "C++(17) compilation is required!"
#endif

#if defined(__clang__) || defined(__GNUC__)
    #define RAYCHEL_FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define RAYCHEL_FUNC_NAME __FUNCSIG__
#else
    #error "Unknown compiler!"
#endif

#ifdef __linux
    #define RAYCHEL_ACTIVE_OS RAYCHEL_OS_LINUX
#elif defined(_WIN32)
    #define RAYCHEL_ACTIVE_OS RAYCHEL_OS_WIN32
#elif defined(__APPLE__)
    #define RAYCHEL_ACTIVE_OS RAYCHEL_OS_DARWIN
#else
    #error "Unknown OS!"
#endif

#endif //!RAYCHEL_COMPAT_H