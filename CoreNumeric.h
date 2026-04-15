//
// Created by STEVEN on 12/04/2026.
//

#ifndef PROGRAMACION_III_TAREA_2_CORENUMERIC_H
#define PROGRAMACION_III_TAREA_2_CORENUMERIC_H

#include <concepts>
#include <iterator>
#include <vector>
#include <iostream>

template<typename C>
concept Iterable = requires(C c)
{
    std::begin(c);
    std::end(c);
};

template<typename T>
concept Addable = requires(T a, T b)
{
    { a + b } -> std::same_as<T>;
};

template<typename T>
concept Divisible = requires(T a, std::size_t n)
{
    {a / n} -> std::convertible_to<T>;
};

template<typename T>
concept Comparable = requires(T a, T b)
{
    { a > b } -> std::convertible_to<bool>;
};

namespace core_numeric {
    template<Iterable C>
    requires Addable<typename C::value_type>
    auto sum(const C& container) {
        using T = typename C::value_type;
        T result{};

        for (const auto& value : container) {
            result = result + value;
        }
        return result;
    }

    template<Iterable C>
    requires Divisible<typename C::value_type>
    auto mean(const C& container) {
        auto total = sum(container);
        return total / container.size();
    }

    template<Iterable C, typename F>
    auto transform_reduce(const C& container, F op) {
        using T = typename C::value_type;
        T result{};

        for (const auto& value : container) {
            result = result + op(value);
        }
        return result;
    }

    template<Iterable C>
    requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto variance(const C& container) {
        using T = typename C::value_type;
        auto m = mean(container);

        auto sum_sq = transform_reduce(container, [m](T x) {
            auto dif = x - m;
            return dif * dif;
        });

        if constexpr (std::is_integral_v<T>) {
            return sum_sq / container.size();
        } else {
            return sum_sq / (container.size() - 1);
        }
    }

    template<Iterable C>
    requires Comparable<typename C::value_type>
    auto max(const C& container) {
        auto it = std::begin(container);
        auto current_max = *it;
        for (; it != std::end(container); ++it) {
            if (*it > current_max) {
                current_max = *it;
            }
        }
        return current_max;
    }

    template<Addable... Args>
    auto sum_variadic(Args... args) {
        return (... + args);
    }

    template<Divisible... Args>
    auto mean_variadic(Args... args) {
        auto m = sum_variadic(args...);
        return (m / sizeof...(args));
    }

    template<typename... Args, typename F>
    auto transform_reduce_v(Args... args, F op) {
        return (... + op(args));
    }

    template <Addable... Args>
    auto variance_variadic(Args... args) {
        constexpr auto n = sizeof...(args);
        using T = std::common_type_t<Args...>;
        T m = mean_variadic(args...);

        T sum_sq = (( (static_cast<T>(args) - m) * (static_cast<T>(args) - m) ) + ...);

        if constexpr (std::is_integral_v<T>) {
            return sum_sq / n;
        } else {
            return sum_sq / (n - 1);
        }
    }

    template<Comparable... Args>
    auto max_variadic(Args... args) {
        auto res = [](auto first, auto... rest) {
            auto m = first;
            ((m = (rest > m ? rest : m)), ...);
            return m;
        }(args...);
        return res;
    }
}

#endif //PROGRAMACION_III_TAREA_2_CORENUMERIC_H