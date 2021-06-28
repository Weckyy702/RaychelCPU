/**
*\file utils.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Utility and core Header file
*\date 2021-03-25
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
#ifndef RAYCHEL_CORE_H
#define RAYCHEL_CORE_H

//convenience headers
#include <cmath>
#include <cstdint>
#include <gsl/gsl>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "CMakeSettings.h"
#include "Logger.h"
#include "RaychelMath/constants.h"
#include "RaychelMath/equivalent.h"
#include "RaychelMath/math.h"
#include "Raychel_assert.h"
#include "compat.h"
#include "export.h"

#ifdef RAYCHEL_DEBUG
    #define RAYCHEL_LOG(...) Logger::debug(RAYCHEL_FUNC_NAME, ": ", __VA_ARGS__, '\n');
#else
    #define RAYCHEL_LOG(...)
#endif

#define RAYCHEL_DELETE_COPY_CTOR(type_name) type_name(const type_name&) = delete;

#define RAYCHEL_DELETE_COPY_OP(type_name) type_name& operator=(const type_name&) = delete;

//NOLINTNEXTLINE: the type name must not be enclosed in parantheses
#define RAYCHEL_DELETE_MOVE_CTOR(type_name) type_name(type_name&&) = delete;

//NOLINTNEXTLINE: the type name must not be enclosed in parantheses
#define RAYCHEL_DELETE_MOVE_OP(type_name) type_name& operator=(type_name&&) = delete;

#define RAYCHEL_MAKE_NONCOPY(type_name)                                                                                          \
    RAYCHEL_DELETE_COPY_CTOR(type_name)                                                                                          \
    RAYCHEL_DELETE_COPY_OP(type_name)

#define RAYCHEL_MAKE_NONMOVE(type_name)                                                                                          \
    RAYCHEL_DELETE_MOVE_CTOR(type_name)                                                                                          \
    RAYCHEL_DELETE_MOVE_OP(type_name)

#define RAYCHEL_MAKE_NONCOPY_NONMOVE(type_name)                                                                                  \
    RAYCHEL_MAKE_NONCOPY(type_name)                                                                                              \
    RAYCHEL_MAKE_NONMOVE(type_name)

#define RAYCHEL_DEFAULT_COPY_CTOR(type_name) type_name(const type_name&) = default;

#define RAYCHEL_DEFAULT_COPY_OP(type_name) type_name& operator=(const type_name&) = default;

//NOLINTNEXTLINE: the type name must not be enclosed in parantheses
#define RAYCHEL_DEFAULT_MOVE_CTOR(type_name) type_name(type_name&&) = default;

//NOLINTNEXTLINE: the type name must not be enclosed in parantheses
#define RAYCHEL_DEFAULT_MOVE_OP(type_name) type_name& operator=(type_name&&) = default;

#define RAYCHEL_MAKE_DEFAULT_COPY(type_name)                                                                                     \
    RAYCHEL_DEFAULT_COPY_CTOR(type_name)                                                                                         \
    RAYCHEL_DEFAULT_COPY_OP(type_name)

#define RAYCHEL_MAKE_DEFAULT_MOVE(type_name)                                                                                     \
    RAYCHEL_DEFAULT_MOVE_CTOR(type_name)                                                                                         \
    RAYCHEL_DEFAULT_MOVE_OP(type_name)

namespace Raychel {

    //NOLINTNEXTLINE(misc-unused-using-decls)
    using gsl::byte, gsl::not_null;
    using std::size_t;

} // namespace Raychel

#endif // !RAYCHEL_CORE_H
