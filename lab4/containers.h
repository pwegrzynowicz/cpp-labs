#ifndef C__LABS_CONTAINER_H
#define C__LABS_CONTAINER_H

#include <cstddef>

// what are the requirements for T?
template<typename T, size_t N>
class container {

    T elements[N];

public:
    void set(size_t n, T const& value) {
        elements[n] = value;
    }

    const T& get(size_t n) const {
        return elements[n];
    }

    size_t size() {
        return N;
    }
};

// template specialization
template<size_t N>
class container<bool, N> {

    using word_t = uint64_t;
    static constexpr size_t bits = sizeof(word_t) * 8;
    static constexpr word_t ONE = 1;

    static constexpr size_t packed_size() {
        return N / bits + (N % bits ? 1 : 0);
    }

    word_t packed_elements[packed_size()] = {0};

    word_t& get_element(size_t n) {
        size_t element_n = n / bits;
        return packed_elements[element_n];
    }

    void set_bit(word_t& element, size_t n, word_t value) {
        size_t bit_n = n % bits;
        element ^= (-value ^ element) & (ONE << bit_n);
    }

    bool get_bit(word_t element, size_t n) {
        size_t bit_n = n % bits;
        return element & (ONE << bit_n);
    }

public:
    void set(size_t n, bool value) {
        word_t& element = get_element(n);
        set_bit(element, n, value);
    }

    bool get(size_t n) {
        word_t element = get_element(n);
        return get_bit(element, n);
    }
};

#endif //C__LABS_CONTAINER_H



