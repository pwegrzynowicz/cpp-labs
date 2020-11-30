#ifndef C__LABS_TRAITS_H
#define C__LABS_TRAITS_H

#include <type_traits>

template<typename T>
struct is_int {
    static constexpr bool value = false;
};

template<>
struct is_int<int> {
    static constexpr bool value = true;
};

template<typename T>
struct is_int_std : std::false_type {};

template<>
struct is_int_std<int> : std::true_type {};

#endif //C__LABS_TRAITS_H
