#ifndef ARGUMENT_PACK_TYPE_HELPER_HHHH_HHHHHHHH___
#define ARGUMENT_PACK_TYPE_HELPER_HHHH_HHHHHHHH___

namespace Generic_Helper{
    template <typename... TArgs>
    struct extra_arg_pack{
        template<template <typename...> class Container, typename T>
            using append_to = Container<T, TArgs...>;

        template <template<typename...> class Container, typename... T>
            using combine = Container<T..., TArgs...>;
    };

    template <template <typename...> class... TTArgs>
    struct extra_targ_pack{
        template <template <typename...> class Container, typename T>
            using append_to = Container<T, TTArgs<T>...>;

        template <template<typename...> class Container, typename... T>
            using combine = Container<T..., TArgs...>;
    };
}

#endif