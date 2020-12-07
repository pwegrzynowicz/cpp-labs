#ifndef C__LABS_ADD_H
#define C__LABS_ADD_H

namespace a1 {

    template<int Val>
    struct num {
        static constexpr int result = Val;
    };

    template<typename Arg1, typename Arg2>
    struct add {
        static constexpr int result = Arg1::result + Arg2::result;
    };

    template<typename Arg>
    using inc = add<Arg, num<1>>;

}

namespace a2 {

    template<int Val>
    struct num {};

    template<typename Arg1, typename Arg2>
    struct add {};

    template<typename Arg>
    using inc = add<Arg, num<1>>;

    template<typename ValueType>
    class executors {
        using value_t = ValueType;

        template<typename Op>
        struct op_executor;

        template<int Val>
        struct op_executor<num<Val>> {
            static constexpr value_t result = Val;
        };

        template<typename Arg1, typename Arg2>
        struct op_executor<add<Arg1, Arg2>> {
            static constexpr value_t result = op_executor<Arg1>::result + op_executor<Arg2>::result;
        };

    public:
        template<typename Op>
        static constexpr value_t execute() {
            return op_executor<Op>::result;
        }
    };

}

namespace a3 {

    template<int Val>
    struct int_num {};

    template<long Val>
    struct long_num {};

    template<typename Arg1, typename Arg2>
    struct add {};

    template<typename Arg>
    using inc = add<Arg, int_num<1>>;

    template<typename ValueType>
    class executors {
        using value_t = ValueType;

        template<typename Op>
        struct op_executor;

        template<int Val>
        struct op_executor<int_num<Val>> {
            static constexpr value_t value(value_t& memory) {
                return Val;
            }
        };

        template<long Val>
        struct op_executor<long_num<Val>> {
            static constexpr value_t value(value_t& memory) {
                return Val;
            }
        };

        template<typename Arg1, typename Arg2>
        struct op_executor<add<Arg1, Arg2>> {
            static constexpr void execute(value_t& memory) {
                // Arg1, Arg2 must have a static constexpr method: value(value_t&)
                // no recursive 'add' allowed, 'long_num', 'int_num' allowed
                memory = op_executor<Arg1>::value(memory) + op_executor<Arg2>::value(memory);
            }
        };

    public:
        template<typename Op>
        static constexpr value_t execute() {
            value_t memory = 0;
            op_executor<Op>::execute(memory);
            return memory;
        }
    };

};


#endif //C__LABS_ADD_H
