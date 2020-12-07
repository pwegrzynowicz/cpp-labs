#include <iostream>

#include "lab4/containers.h"
#include "lab4/fibbonacci.h"
#include "lab4/traits.h"
#include "lab4/list.h"
#include "lab4/add.h"

class a {};

using mixed_list = lst::list<char, int, container<int, 1>, a, int>;
using int_list = typename lst::filter<is_int, mixed_list>::type;

int main() {
    container<int, 5> int_container{};
    container<bool, 65> bool_container{};

    std::cout << "int container size: " << sizeof(int_container) << std::endl;
    std::cout << "bool container size: " << sizeof(bool_container) << std::endl;

    static_assert(Fib<5>::result == 5);
    static_assert(fib(5) == 5);

    static_assert(is_int<int>::value);
    static_assert(!is_int<char>::value);

    static_assert(mixed_list::size == 5);
    static_assert(int_list::size == 2);

    static_assert(a1::add<a1::num<2>, a1::num<2>>::result == 4);
    static_assert(a1::add<a1::add<a1::num<2>, a1::num<2>>, a1::num<2>>::result == 6);
    static_assert(a1::inc<a1::num<1>>::result == 2);

    static_assert(a2::executors<unsigned char>::execute<a2::add<a2::num<256>, a2::num<0>>>() == 0);
    static_assert(a2::executors<int>::execute<a2::add<a2::num<256>, a2::num<0>>>() == 256);

    static_assert(a3::executors<int64_t>::execute<a3::add<a3::int_num<256>, a3::long_num<0>>>() == 256);
}
