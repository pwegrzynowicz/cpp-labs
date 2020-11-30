#ifndef C__LABS_FIBBONACCI_H
#define C__LABS_FIBBONACCI_H

#include <cstddef>

template<size_t N>
struct Fib {
    static constexpr uint64_t result = Fib<N - 1>::result + Fib<N - 2>::result;
};

template<>
struct Fib<0> {
    static constexpr uint64_t result = 0;
};

template<>
struct Fib<1> {
    static constexpr uint64_t result = 1;
};

constexpr uint64_t fib(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

#endif //C__LABS_FIBBONACCI_H
