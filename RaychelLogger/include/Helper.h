/**
*\file Helper.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Helper include file for RaychelLogger
*\date 2021-06-13
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

#ifndef HELPER_H_
#define HELPER_H_

#ifdef _WIN32
    #ifdef RAYCHELLOGGER_EXPORTS
        #define LOGGER_EXPORT __declspec(dllexport)
    #else
        #define LOGGER_EXPORT __declspec(dllimport)
    #endif
#else
    #define LOGGER_EXPORT
#endif

#include <string_view>
#include <type_traits>

namespace Logger::details {

    template <size_t off_, typename = std::enable_if_t<(off_ < sizeof(uint32_t))>>
    constexpr uint32_t bit =  1U << off_;

    template <typename S, typename T, typename = void>
    struct is_to_stream_writable : std::false_type
    {};

    template <typename S, typename T>
    struct is_to_stream_writable<S, T, std::void_t<decltype(std::declval<S&>() << std::declval<T>())>> : std::true_type
    {};

    template <typename S, typename T>
    constexpr bool is_to_stream_writable_v = is_to_stream_writable<S, T>::value;

    template <typename T, typename = void>
    struct is_std_hashable : std::false_type
    {};

    template <typename T>
    struct is_std_hashable<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>> : std::true_type
    {};

    template <typename T>
    constexpr bool is_std_hashable_v = is_std_hashable<T>::value;

    //thank you to einpoklum at https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
    template <typename T>
    [[nodiscard]] constexpr std::string_view type_name() noexcept
    {
        std::string_view name;
        std::string_view prefix;
        std::string_view suffix;
#ifdef __clang__
        name = __PRETTY_FUNCTION__;
        prefix = "std::string_view Logger::details::type_name() [T = ";
        suffix = "]";
#elif defined(__GNUC__)
        name = __PRETTY_FUNCTION__;
        prefix = "constexpr std::string_view Logger::details::type_name() [with T = ";
        suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
        name = __FUNCSIG__;
        prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl Logger::details::type_name<";
        suffix = ">(void) noexcept";
#endif
        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());
        return name;
    }

    template <typename F>
    class Finally
    {
    public:
        explicit Finally(F&& f) : f_{std::forward<F>(f)}
        {}

        Finally(const Finally&) = default;
        Finally(Finally&&) noexcept = default;

        Finally& operator=(const Finally&) = default;
        Finally& operator=(Finally&&) noexcept = default;

        ~Finally() noexcept
        {
            f_();
        }

    private:
        F f_;
    };
} // namespace Logger::details

#endif /* HELPER_H_ */
