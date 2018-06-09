//
// Created by doom on 18/09/17.
//

#pragma once
#include <typeinfo>
#include <type_traits>
#include <cstddef>

namespace shiva::meta
{
    template <typename ...Types>
    struct TypeList
    {
    };

    namespace list
    {
        namespace detail
        {
            template <typename List, typename ...ToAdd>
            struct PushBack;

            template <typename ...ListTypes, typename ...ToAdd>
            struct PushBack<TypeList<ListTypes...>, ToAdd...>
            {
                using type = TypeList<ListTypes..., ToAdd...>;
            };

            template <typename List, typename ...ToAdd>
            struct PushFront;

            template <typename ...ListTypes, typename ...ToAdd>
            struct PushFront<TypeList<ListTypes...>, ToAdd...>
            {
                using type = TypeList<ToAdd..., ListTypes...>;
            };

            template <typename List, typename OtherList>
            struct Concat;

            template <typename ...ListTypes, typename ...OtherListTypes>
            struct Concat<meta::TypeList<ListTypes...>, meta::TypeList<OtherListTypes...>>
            {
                using type = meta::TypeList<ListTypes..., OtherListTypes...>;
            };

            template <typename List, typename ToFind>
            struct Contains;

            template <typename T, typename ...ListTypes, typename ToFind>
            struct Contains<TypeList<T, ListTypes...>, ToFind> :
                std::bool_constant<std::is_same_v<T, ToFind> || Contains<TypeList<ListTypes...>, ToFind>()>
            {
            };

            template <typename T, typename ToFind>
            struct Contains<TypeList<T>, ToFind> : std::bool_constant<std::is_same_v<T, ToFind>>
            {
            };

            template <typename List, typename OtherList>
            struct ContainsList;

            template <typename List, typename T>
            struct ContainsList<List, meta::TypeList<T>> : std::bool_constant<Contains<List, T>::value>
            {
            };

            template <typename List, typename T, typename ...OtherListTypes>
            struct ContainsList<List, meta::TypeList<T, OtherListTypes...>> :
                std::bool_constant<Contains<List, T>::value
                                   && ContainsList<List, meta::TypeList<OtherListTypes...>>::value>
            {
            };

            template <typename List>
            struct Length;

            template <typename ...ListTypes>
            struct Length<TypeList<ListTypes...>> : std::integral_constant<size_t, sizeof ...(ListTypes)>
            {
            };

            template <typename List, typename ToFind>
            struct Position;

            template <typename T, typename ...ListTypes, typename ToFind>
            struct Position<meta::TypeList<T, ListTypes...>, ToFind> :
                std::integral_constant<size_t, 1 + Position<meta::TypeList<ListTypes...>, ToFind>()>
            {
            };

            template <typename ...ListTypes, typename ToFind>
            struct Position<meta::TypeList<ToFind, ListTypes...>, ToFind> : std::integral_constant<size_t, 0>
            {
            };

            template <typename List, size_t pos>
            struct At;

            template <typename T, typename ...ListTypes, size_t pos>
            struct At<meta::TypeList<T, ListTypes...>, pos>
            {
                using type = typename At<meta::TypeList<ListTypes...>, pos - 1>::type;
            };

            template <typename T, typename ...ListTypes>
            struct At<meta::TypeList<T, ListTypes...>, 0>
            {
                using type = T;
            };

            template <typename List, template <typename> typename Apply>
            struct Transform;

            template <typename ...ListTypes, template <typename> typename Apply>
            struct Transform<meta::TypeList<ListTypes...>, Apply>
            {
                using type = meta::TypeList<Apply<ListTypes>...>;
            };

            template <typename List, template <typename ...> typename To>
            struct Convert;

            template <typename ...ListTypes, template <typename ...> typename To>
            struct Convert<meta::TypeList<ListTypes...>, To>
            {
                using type = To<ListTypes...>;
            };

            template <typename List, typename ...Rest>
            struct TypeListUniqAux;

            template <typename List, typename T>
            struct TypeListUniqAux<List, T>
            {
                using type = std::conditional_t<Contains<List, T>::value,
                    List, typename PushBack<List, T>::type>;
            };

            template <typename List, typename T, typename ...Rest>
            struct TypeListUniqAux<List, T, Rest...>
            {
                using list = std::conditional_t<Contains<List, T>::value,
                    List, typename PushBack<List, T>::type>;
                using type = typename TypeListUniqAux<list, Rest...>::type;
            };

            template <typename List>
            struct Uniq;

            template <typename T, typename ...ListTypes>
            struct Uniq<meta::TypeList<T, ListTypes...>>
            {
                using type = typename TypeListUniqAux<meta::TypeList<T>, ListTypes...>::type;
            };

            template <typename List, template <typename> typename Pred, typename ...Rest>
            struct TypeListFilterAux;

            template <typename List, template <typename> typename Pred, typename T>
            struct TypeListFilterAux<List, Pred, T>
            {
                using type = std::conditional_t<Pred<T>::value, typename PushBack<List, T>::type, List>;
            };

            template <typename List, template <typename> typename Pred, typename T, typename ...Rest>
            struct TypeListFilterAux<List, Pred, T, Rest...>
            {
                using list = std::conditional_t<Pred<T>::value, typename PushBack<List, T>::type, List>;
                using type = typename TypeListFilterAux<list, Pred, Rest...>::type;
            };

            template <typename List, template <typename> typename Pred>
            struct Filter;

            template <typename ...ListTypes, template <typename> typename Pred>
            struct Filter<meta::TypeList<ListTypes...>, Pred>
            {
                using type = typename TypeListFilterAux<meta::TypeList<>, Pred, ListTypes...>::type;
            };
        };

        /**
         * Push one or more types at the back of a TypeList
         *
         * @tparam List         the list to add into
         * @tparam ToAdd        the types to add
         */
        template <typename List, typename ...ToAdd>
        using PushBack = typename detail::PushBack<List, ToAdd...>::type;

        /**
         * Push one or more types at the front of a TypeList
         *
         * @tparam List         the list to add into
         * @tparam ToAdd        the types to add
         */
        template <typename List, typename ...ToAdd>
        using PushFront = typename detail::PushFront<List, ToAdd...>::type;

        /**
         * Concatenate two TypeLists
         *
         * @tparam List         the first list
         * @tparam OtherList    the second list
         */
        template <typename List, typename OtherList>
        using Concat = typename detail::Concat<List, OtherList>::type;

        /**
         * Check whether a given type is contained in a TypeList
         *
         * @tparam List         the list to search into
         * @tparam ToFind       the type to search
         */
        template <typename List, typename ToFind>
        using Contains = detail::Contains<List, ToFind>;

        /**
         * Check whether all the types in a TypeList are contained in another TypeList
         *
         * @tparam List         the list to search into
         * @tparam OtherList    the list of types to search
         */
        template <typename List, typename OtherList>
        using ContainsList = detail::ContainsList<List, OtherList>;

        template <typename List>
        using Length = detail::Length<List>;

        /**
         * Find the position of a type in a TypeList
         *
         * @tparam List         the list to search into
         * @tparam ToFind       the types to add
         */
        template <typename List, typename ToFind>
        using Position = detail::Position<List, ToFind>;

        /**
         * Get the type at a given position in a TypeList
         *
         * @tparam List         the list to search into
         * @tparam pos          the position at which to search
         */
        template <typename List, size_t pos>
        using At = typename detail::At<List, pos>::type;

        /**
         * Apply a metafunction to each type in a TypeList
         *
         * @tparam List         the list
         * @tparam Apply        the metafunction to apply
         */
        template <typename List, template <typename> typename Apply>
        using Transform = typename detail::Transform<List, Apply>::type;

        /**
         * Convert a TypeList into another variadic-templated type
         *
         * @tparam List         the list to add into
         * @tparam To           the target type
         */
        template <typename List, template <typename ...> typename To>
        using Convert = typename detail::Convert<List, To>::type;

        /**
         * Remove the duplicate types in a TypeList
         *
         * @tparam List         the list
         */
        template <typename List>
        using Uniq = typename detail::Uniq<List>::type;

        /**
         * Remove the types not matching a predicate from a TypeList
         *
         * @tparam List     the list to filter
         * @tparam Pred     the predicate
         */
        template <typename List, template <typename> typename Pred>
        using Filter = typename detail::Filter<List, Pred>::type;
    };
};