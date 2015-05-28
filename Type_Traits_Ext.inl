#include <type_traits>

namespace Type_Trait{
    template <typename T, typename F>
    struct conditional<std::true_type, T, F>{
        typedef T type;
    };

    template <typename T, typename F>
    struct conditional<std::false_type, T, F>{
        typedef F type;
    };

    template <typename T1, typename... Tn>
    struct any_true{
        typedef typename conditional<
            typename any_true<T1>::type,
            std::true_type, typename any_true<Tn...>::type
            >::type type;
    };

    template <>
    struct any_true<std::false_type>{
        typedef std::false_type type;
    };

    template <>
    struct any_true<std::true_type>{
        typedef std::true_type type;
    };

    template <typename T1, typename T2, typename T3, typename... Tn>
    struct count_matches<T1, T2, T3, Tn...>{
        private:
            typedef count_matches<T1, T2> final_type;
            typedef count_matches<T1, T3, Tn...> inner_type;
        public:
        
        typedef typename conditional<
            typename final_type::type,
            std::true_type, typename inner_type::type
            >::type type;
        static constexpr std::size_t match = final_type::match+inner_type::match;
    };

    template <typename T>
    struct count_matches<T, T>{
        typedef std::true_type type;
        static constexpr std::size_t match = 1;
    };

    template <typename T1, typename T2>
    struct count_matches<T1, T2>{
        typedef std::false_type type;
        static constexpr std::size_t match = 0;
    };

    template <typename Derived, typename Base1, typename... BaseN>
    struct find_base<Derived, Base1, BaseN...>{
        private:
            typedef find_base<Derived, Base1> final_type;
            typedef find_base<Derived, BaseN...> inner_type;
        public:
        
        typedef typename any_true<
            typename final_type::type,
            typename inner_type::type
            >::type type;
        
        typedef typename conditional<
            typename final_type::type,
            typename final_type::base,
            typename inner_type::base
            >::type base;
    };


    template <typename Derived, typename Base>
    struct find_base<Derived, Base>{
        typedef typename std::is_base_of<Base, Derived>::type		type;
        typedef typename conditional<type, Base, Derived>::type 	base;
    };

    template <typename Derived>
    struct find_base<Derived>{
        typedef std::false_type		type;
        typedef Derived 			base;
    };

    namespace Helper{
        template <std::size_t Index, std::size_t N, typename T, typename... Tn>
        struct switch_case{
            typedef typename Helper::switch_case<Index+1, N, Tn...>::type type;
        };
        
        template <std::size_t N, typename T, typename... Tn>
        struct switch_case<N, N, T, Tn...>{
            typedef T type;
        };
    }

    template <std::size_t N, typename T, typename... Tn>
    struct switch_case{
        typedef typename Helper::switch_case<0, N, T, Tn...>::type type;
    };

    template <typename T, typename... Tn>
    struct switch_case<0, T, Tn...>{
        typedef T type;
    };

    template <>
    struct negate<std::true_type>{
        typedef std::false_type type;
    };

    template <>
    struct negate<std::false_type>{
        typedef std::true_type type;
    };

    template <typename Base, typename Derived>
    struct is_derivation_of{
        typedef typename negate
            <typename std::is_base_of<Base, Derived>::type>::type type;
    }
}