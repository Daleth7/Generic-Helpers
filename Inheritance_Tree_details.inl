namespace Cendent_Tree_detail_{
    typedef void                    Node_Null_;
    typedef type_tuple<Node_Null_>  Null_;

    template <typename, typename...>
    struct Node_;

#ifndef QUICK_CENDENT_
    template <
        template <typename...> class Container,
        typename NextNode, typename... Nodes
    >
    struct insert_nodes_raw_{
        typedef typename insert_nodes_raw_<
            Container, typename NextNode::next,
            Nodes..., typename NextNode::node
            >::type type;
    };

    template <template <typename...> class Container, typename... Nodes>
    struct insert_nodes_raw_<Container, Null_, Nodes...>{
        typedef Container<Nodes..., Node_Null_> type;
    };

    template <
        template <typename, typename> class Check,
        typename Nodet, typename... Noden
    >
    struct check_each_{
        typedef typename Type_Trait::any_true<
                typename Check<
                    typename Nodet::type,
                    typename Noden::type
                    >::type...
            >::type type;
    };

    template <template <typename, typename> class Check, typename... Noden>
    struct check_each_<Check, Node_Null_, Noden...>{
        typedef typename std::false_type type;
    };

    template <
        template <typename, typename> class Check,
        typename Nodet, typename... Noden
    >
    struct insert_verify_helper_{
        typedef typename Type_Trait::conditional<
            typename check_each_<Check, Nodet, Noden...>::type,
            Null_, Nodet
            >::type type;
    };

    template <
        template <typename...> class Container,
        template <typename, typename> class Check,
        class NodeTuple, typename Node0, typename... Nodes
    >
    struct insert_verify_{
        typedef typename insert_verify_<
            Container, Check,
            typename NodeTuple::next, Node0, Nodes...,
            typename insert_verify_helper_<
                Check, typename NodeTuple::type,
                Node0, Nodes...
                >::type
            >::type type;
    };

    template <
        template <typename...> class Container,
        template <typename, typename> class Check,
        typename Node0, typename... Nodes
    >
    struct insert_verify_<Container, Check, Null_, Node0, Nodes...>{
        typedef Container<Node0, Nodes...> type;
    };

    template <
        template <typename...> class Container,
        template <typename, typename> class Check,
        typename NextNode, typename... Nodes
    >
    struct insert_nodes_{
        typedef typename insert_nodes_raw_<Container, NextNode, Nodes...>::type
                                                                    all_nodes;

        typedef typename insert_verify_<
            Container, Check,
            typename all_nodes::next, typename all_nodes::type
            >::type                                                 type;
    };

    template <
        template <typename...> class NodeType,
        unsigned I, unsigned TargetIndex,
        typename Root, typename... IncludeList
    >
    struct swap_root_helper_{
        template <typename T0, typename... Tn>
        using type = typename swap_root_helper_
            <NodeType, I+1u, TargetIndex, Root, T0, IncludeList...>
            :: template type<Tn...>;
    };

    template <
        template <typename...> class NodeType, unsigned TargetIndex,
        typename Root, typename... IncludeList
    >
    struct swap_root_helper_
        <NodeType, TargetIndex, TargetIndex, Root, IncludeList...>
    {
        template <typename T0, typename... Tn>
        using type = NodeType<T0, IncludeList..., Root, Tn...>;
    };

    template <
        template <typename...> class NodeType, unsigned TargetIndex,
        typename Root, typename... TestList
    >
    struct swap_root_{
        typedef typename swap_root_helper_<NodeType, 0u, TargetIndex, Root>
            :: template type<TestList...> type;
    };

    template <
        unsigned Size, unsigned I,
        typename Root, template <typename, typename> class Check,
        typename... Tn
    >
    struct create_nodes_{
        using all_types = type_tuple<Tn...>;
        using next_root = typename get<I-1u, all_types>::type;

        typedef
            typename Type_Trait::conditional<
                typename Check<next_root, Root>::type,
                typename swap_root_<Node_, I-1u, Root, Tn...>::type,
                Null_
            >::type                                             node;

        typedef create_nodes_<Size, I+1u, Root, Check, Tn...>   next;

        template< template <typename...> class Container>
        using insert_to = insert_nodes_<Container, Check, next, node>;
    };

    template <
        unsigned Size,
        typename Root, template <typename, typename> class Check,
        typename... Tn
    >
    struct create_nodes_<Size, Size, Root, Check, Tn...>{
        using all_types = type_tuple<Tn...>;
        using next_root = typename get<Size-1u, all_types>::type;

        typedef
            typename Type_Trait::conditional<
                typename Check<next_root, Root>::type,
                typename swap_root_<Node_, Size-1u, Root, Tn...>::type,
                Node_Null_
            >::type                                     node;

        typedef Null_                                   next;

        template< template <typename...> class Container>
        using insert_to = insert_nodes_<Container, Check, next, node>;
    };

#else

    template <
        template <typename...> class Container,
        typename NextNode, typename... Nodes
    >
    struct insert_nodes_{
        typedef typename Type_Trait::conditional<
                typename std::is_same
                    <Null_, typename NextNode::next>::type,
                Container<Nodes..., typename NextNode::node>,
                typename insert_nodes_<
                    Container,
                    typename NextNode::next,
                    Nodes..., typename NextNode::node
                    >::type
            >::type type;
    };

    template <
        template <typename...> class Container,
        typename... Nodes
    >
    struct insert_nodes_<Container, Null_, Nodes...>{
        typedef Container<Nodes...> type;
    };

    template <
        unsigned Size, unsigned I,
        typename Root, template <typename, typename> class Check,
        typename... Tn
    >
    struct create_nodes_{
        using all_types = type_tuple<Tn...>;

        typedef
            typename Type_Trait::conditional<
                typename Check<typename get
                    <I-1u, all_types>::type, Root>::type,
                Node_<typename get
                    <I-1u, all_types>::type, Tn...>,
                Null_
            >::type                                             node;

        typedef create_nodes_<Size, I+1u, Root, Check, Tn...>   next;

        template< template <typename...> class Container>
        using insert_to = insert_nodes_<Container, next, node>;
    };

    template <
        unsigned Size,
        typename Root, template <typename, typename> class Check,
        typename... Tn
    >
    struct create_nodes_<Size, Size, Root, Check, Tn...>{
        using all_types = type_tuple<Tn...>;

        typedef
            typename Type_Trait::conditional<
                typename Check
                    <typename get<Size-1u, all_types>::type, Root>::type,
                Node_
                    <typename get<Size-1u, all_types>::type, Tn...>,
                Null_
            >::type                                         node;

        typedef Null_                                       next;

        template< template <typename...> class Container>
        using insert_to = insert_nodes_<Container, next, node>;
    };

#endif

    template <typename Derived, typename Base>
    struct is_derivation_switched_{
        typedef typename Type_Trait::is_derivation_only
            <Base, Derived>::type type;
    };

    template <typename T, typename... Tn>
    struct Node_{
        typedef type_tuple<Tn...>               all_types;
        typedef T                               type;

        typedef typename Cendent_Tree_detail_::create_nodes_
            <all_types::size, 1u, T, Type_Trait::is_base_only, Tn...>
            :: template insert_to<type_tuple>::type
                                                antecendent_tuple;

        typedef typename Cendent_Tree_detail_::create_nodes_
            <all_types::size, 1u, T, is_derivation_switched_, Tn...>
            :: template insert_to<type_tuple>::type
                                                descendent_tuple;
    };

    template <unsigned, typename>
    struct get_;

    template <unsigned, unsigned I, typename TupleType>
    struct get_next_if_{
        typedef typename get_
            <I, typename TupleType::next>::type type;
    };

    template <unsigned I, typename TupleType>
    struct get_next_if_<1u, I, TupleType>{
        typedef typename TupleType::type type;
    };

    template <unsigned I, typename TupleType>
    struct get_{
        typedef typename Type_Trait::conditional<
            typename std::is_same
                <typename get<0u, TupleType>::type, Null_>::type,
            typename get_next_if_
                <TupleType::size, I, TupleType>::type,
            typename get_next_if_
                <TupleType::size, I-1u, TupleType>::type
            >::type type;
    };

    template <typename TupleType>
    struct get_<0u, TupleType>{
        typedef typename Type_Trait::conditional<
            typename std::is_same
                <typename get<0u, TupleType>::type, Null_>::type,
            typename get_next_if_
                <TupleType::size, 0u, TupleType>::type,
            typename TupleType::type
            >::type type;
    };
}

    //Generalized tree that has to be given a root
template <typename NodeType>
struct Cendent{
        //Going out-of-bounds shall result in a void
    template <unsigned I>
    using antecendent_node
        = typename Cendent_Tree_detail_::get_
        <I, typename NodeType::antecendent_tuple>::type;
    template <unsigned I>
    using descendent_node
        = typename Cendent_Tree_detail_::get_
        <I, typename NodeType::descendent_tuple>::type;

    static constexpr unsigned antecendent_size
        = NodeType::antecendent_tuple::size - count_type_population<
            typename NodeType::antecendent_tuple,
            Cendent_Tree_detail_::Null_
            >::value - count_type_population<
                typename NodeType::antecendent_tuple,
                Cendent_Tree_detail_::Node_Null_
                >::value;
    static constexpr unsigned descendent_size
        = NodeType::descendent_tuple::size - count_type_population<
            typename NodeType::descendent_tuple,
            Cendent_Tree_detail_::Null_
            >::value - count_type_population<
                typename NodeType::descendent_tuple,
                Cendent_Tree_detail_::Node_Null_
                >::value;

    template <unsigned I>
    using antecendent = typename antecendent_node<I>::type;
    template <unsigned I>
    using descendent = typename descendent_node<I>::type;
    
};

template <typename T, typename... Tn>
struct Cendent_Tree
    : public Cendent<Cendent_Tree_detail_::Node_<T, Tn...> >
{
    typedef Cendent_Tree_detail_::Node_<T, Tn...> root;
};