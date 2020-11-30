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
    template<typename... Ts, typename... Us, typename... Rest>
    struct concat<list<Ts...>, list<Us...>, Rest...> {
        using type = typename concat<list<Ts..., Us...>, Rest...>::type;
    };

    // if a predicate Pred is true for a given T, then this type represents a single-element list: list<T>,
    // otherwise it's an empty list: list<>
    template<template<typename> class Pred, typename T>
    using check_predicate = std::conditional_t<Pred<T>::value, list<T>, list<>>;

    template<template<typename> class Pred, typename List>
    struct filter;
    // 'template<typename...> class Src' and 'Src<Ts...>' make this working on any template type with a parameter pack,
    // not only list<...> (!)
    template<template<typename> class Pred, template<typename...> class Src, typename... Ts>
    struct filter<Pred, Src<Ts...>> {
        // check_predicate<Pred, Ts>... - evaluates check_predicate for each element of the paramater pack Ts,
        // producing a list of lists (each element is a single-element list or an empty list)
        // concat - concatenates the list of lists into one list
        using type = typename concat<check_predicate<Pred, Ts>...>::type;
    };
}
#endif //C__LABS_LIST_H
