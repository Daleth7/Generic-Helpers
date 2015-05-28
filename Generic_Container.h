#ifndef GENERIC_CONTAINER_HELPERS_HHHHHH_HHHH_HHHHHHH_
#define GENERIC_CONTAINER_HELPERS_HHHHHH_HHHH_HHHHHHH_

namespace Generic_Helper{
        //For non-LIFO, non-FIFO, and non-mapping containers (except std::set)
    template <template <typename...> class>
    struct Container;

    template <template <typename, typename> class Container>
    struct Container<Container>{
        template <typename Value_Type>
        static void push(const Value_Type& new_val, Container<Value_Type>& con)
            {con.push_back(new_val);}
    };

    template <template <typename, class, class> class Container>
    struct Container<Container>{
        template <typename Value_Type>
        static void push(const Value_Type& new_val, Container<Value_Type>& con)
            {con.insert(new_val);}
    };
}

#endif