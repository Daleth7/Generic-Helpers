#ifndef TYPE_TUPLE_CLASS_TEMPLATE_DEFINITION_HHH___HHHH_
#define TYPE_TUPLE_CLASS_TEMPLATE_DEFINITION_HHH___HHHH_

namespace Generic_Helper{
    template<typename T, typename... Tn>
    struct type_tuple{
        typedef T                   type;
        typedef type_tuple<Tn...>   next;
        static constexpr unsigned size = 1+sizeof...(Tn);
    };

    template <typename T>
    struct type_tuple<T>{
        typedef T type;
        static constexpr unsigned size = 1;
    };

    template <unsigned Index, class TypeTupleType>
    struct get{
        typedef typename get<Index-1, typename TypeTupleType::next>::type type;
    };

    template <class TypeTupleType>
    struct get<0u, TypeTupleType>{
        typedef typename TypeTupleType::type type;
    };
}

#endif