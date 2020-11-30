#ifndef C__LABS_LIST_H
#define C__LABS_LIST_H

#include <type_traits>

namespace lst {
    template<typename... Ts>
    struct list {
        static constexpr size_t size = sizeof...(Ts);
    };

    template<typename... Lists>
    struct concat;
    template<>
    struct concat<> {
        using type = list<>;
    };
    template<typename... Ts>
    struct concat<list<Ts...>> {
        using type = list<Ts...>;
    };
    template<typename... Ts, typename... Us>
    struct concat<list<Ts...>, list<Us...>> {
        using type = list<Ts..., Us...>;
    };
    template<typename... Ts, typename... Us, typename... Rest>
    struct concat<list<Ts...>, list<Us...>, Rest...> {
        using type = typename concat<list<Ts..., Us...>, Rest...>::type;
    };

    template<template<typename> class Pred, typename T>
    using pred = std::conditional_t<Pred<T>::value, list<T>, list<>>;

    template<template<typename> class Pred, typename List>
    struct filter;

    template<template<typename> class Pred, typename... Ts>
    struct filter<Pred, list<Ts...>> {
        using type = typename concat<pred<Pred, Ts>...>::type;
    };
}
#endif //C__LABS_LIST_H
