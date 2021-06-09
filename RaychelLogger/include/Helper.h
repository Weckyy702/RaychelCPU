/*
 * Helper.h
 *
 *  Created on: 18.02.2021
 *      Author: weckyy
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <string_view>
#include <type_traits>

namespace Logger {

    namespace details {

        template <size_t off_, typename = std::enable_if_t<(off_ < sizeof(uint32_t))>>
        [[nodiscard]] constexpr uint32_t bit() noexcept
        {
            return 1UL << off_;
        }

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
            std::string_view name, prefix, suffix;
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
    } // namespace details
} // namespace Logger

#endif /* HELPER_H_ */
