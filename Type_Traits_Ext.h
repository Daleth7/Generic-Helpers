#ifndef CPLSUPLUS_TYPE_TRAITS_EXTENSION___HHH____
#define CPLSUPLUS_TYPE_TRAITS_EXTENSION___HHH____

#include <cstddef>

namespace Type_Trait{
    /*  conditional<typename ToF_Type, typename T, typename F>,
        like its standard counterpart, provides either type T
        or F depending on ToF_Type.

        Template Parameters:
            * ToF_Type - either std::true_type or std::false_type
            * T - member type if ToF_Type is std::true_type
            * F - member type if ToF_Type is std::false_type
        Members:
            * type - Either T or F depending on ToF_Type being
                std::true_type or std::false_type, respectively.

        Example use:
                //Creates an int type variable
            Type_Trait::conditional<
                std::is_same<int, int>::type,   //Condition
                int, char                       //Types to resolve to
                >::type var;
                //Creates a char type variable
            conditional<std::is_same<double, int>::type, int, char>::type var;
    */
    template <typename ToF_Type, typename T, typename F>
        struct conditional;

    /*  any_true<T1, Tn...> takes a list of std::integral_constant
        instantiations and determines if any of them is std::true_type.
        At least one parameter must be provided.

        Template Parameters:
            * T1 - a std::integral_constant instantiation
            * Tn... - additional instantiations
        Members:
            * type - equivalent to std::true_type if at least one of the
                parameters is std::true_type. std::false_type otherwise.

        Example use:
            typedef std::true_type tt;
            typedef std::false_type ft;
                //Creates a char type variable
            Type_Trait::conditional<
                Type_Trait::any_true<ft, ft, ft, ft, ft, ft, ft, tt>::type,
                char, int
            > var;
    */
    template <typename T1, typename... Tn>
        struct any_true;

    /*  count_matches<T1, T2, Tn...> takes type T1 and compares it to
        the rest of the parameter list, counting the total number of
        types that match it. At least two parameters must be provided.

        Template Parameters:
            * T1 - the type to check for
            * T2 - the first type to check against
            * Tn... - additional types to check against
        Members:
            * type - equivalent to std::true_type if at least one match
                is found. std::false_type otherwise.
            * match - a std::size_t variable that stores the number of
                matches found.

        Example use:
            assert(Type_Trait::count_matches<int, int, char, int>::match == 2);
    */
    template <typename T1, typename T2, typename... Tn>
        struct count_matches;

    /*  find_base<Derived, BaseN...> looks for the first type in the BaseN
        parameter pack that is a base type of Derived. Note that only the
        first result is found and retrievable. If none of the types is a
        base type of Derived or there is no BaseN list provided, the member
        type will be equivalent to Derived.

        Template Parameters:
            * Derived - the type whose base is looked for
            * BaseN... - the list of types to check
        Members:
            * type - equivalent to std::true_type if a base type was found.
                std::false_type otherwise.
            * base - the type of the first result that is a base type of
                Derived. If no match was found or no list was provided,
                this type is equivalent to Derived.

        Example use:
            assert(Type_Trait::count_matches<int, int, char, int>::match == 2);
    */
    template <typename Derived, typename... BaseN>
        struct find_base;

    /*  switch_case<N, T, Tn...> is like the switch-case expression except
        this is for selecting types given an index number. This also means
        this class is similar to std::tuple and std::get. This class is
        to std::conditional as the switch-case expression is to the
        if-else expression.

        Template Parameters:
            * N - a std::size_t object. This is the compile-time index that
                chooses a type out of the list.
            * T - the first type/case
            * Tn... - additional cases
        Members:
            * type - the resultant type from choosing the (N+1)th type from
                the type list. For example, if N == 0, type would be
                equivalent to T.

        Example use:
            constexpr std::size_t get_half(std::size_t n)
                {return n >> 1;}

                //Creates a char type variable
            Type_Trait::switch_case<
                get_half(6),                //The condition / index
                int,                        //Case 0
                float,                      //Case 1
                std::size_t,                //Case 2
                char,                       //Case 3
                double                      //Case 4
            >::type var;
    */
    template <std::size_t N, typename T, typename... Tn>
        struct switch_case;

    /*  negate<T> is simply for turning std::true_type to std::false_type
        and etc.

        Template Parameters:
            * T - the type to negate; either std::true_type or std::false_type
        Members:
            * type - the opposite of T; either std::false_type or std::true_type

        Example use:
            typedef Type_Trait::negate<std::true_type>::type false_type;
    */
    template <typename T>
        struct negate;

    /*  is_derivation_of<Base, Derived> does the opposite of std::is_base_of.

        Template Parameters:
            * Base - the base type to check against
            * Derived - the testee to check against the Base
        Members:
            * type - either std::true_type or std::false_type
    */
    template <typename Base, typename Derive>
        struct is_derivation_of;
}

#include "Type_Traits_Ext.inl"

#endif