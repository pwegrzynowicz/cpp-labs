#include <iostream>

#include "lab4/containers.h"
#include "lab4/fibbonacci.h"
#include "lab4/traits.h"
#include "lab4/list.h"

using mixed_list = lst::list<char, int, container<int, 1>, int>;
using int_list = typename lst::filter<is_int, mixed_list>::type;

int main() {
    container<int, 5> int_container{};
    container<bool, 63> bool_container{};

    std::cout << "int container size: " << sizeof(int_container) << std::endl;
    std::cout << "bool container size: " << sizeof(bool_container) << std::endl;

    static_assert(Fib<5>::result == 5);
    static_assert(fib(5) == 5);

    static_assert(is_int<int>::value);
    static_assert(!is_int<char>::value);

    static_assert(mixed_list::size == 4);
    static_assert(int_list::size == 2);

    return 0;
}
