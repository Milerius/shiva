//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <utility>
#include <functional>
#include <optional>
#include <type_traits>
#include <shiva/pp/pp_stringify.hpp>
#include <shiva/meta/type_traits.hpp>
#include <shiva/meta/visitor.hpp>
#include <shiva/meta/map.hpp>

namespace shiva::refl
{
    template <typename T>
    using member_map_t = decltype(T::reflected_members());

    template <typename T>
    using function_map_t = decltype(T::reflected_functions());

    template <typename T>
    using class_name_t = decltype(T::class_name());

    template <typename T>
    using has_reflectible_members = meta::is_detected<member_map_t, T>;

    template <typename T>
    inline constexpr bool has_reflectible_members_v = has_reflectible_members<T>::value;

    template <typename T>
    using has_reflectible_functions = meta::is_detected<function_map_t, T>;

    template <typename T>
    inline constexpr bool has_reflectible_functions_v = has_reflectible_functions<T>::value;

    template <typename T>
    using has_reflectible_class_name = meta::is_detected<class_name_t, T>;

    template <typename T>
    inline constexpr bool has_reflectible_class_name_v = has_reflectible_class_name<T>::value;

    template <typename T>
    using is_reflectible = std::disjunction<has_reflectible_members<T>, has_reflectible_functions<T>>;

    template <typename T>
    inline constexpr bool is_reflectible_v = is_reflectible<T>::value;

    namespace details
    {
        constexpr std::string_view skipNamespaceName(const std::string_view v) noexcept
        {
            return (v[0] == ':' && v[1] == ':') ? std::string_view{v.data() + 2, v.length() - 2}
                                                : skipNamespaceName({v.data() + 1, v.length() - 1});
        }
    }

#define reflect_member(member)          shiva::refl::details::skipNamespaceName(pp_stringviewify(member)), member

#define reflect_function(func)          shiva::refl::details::skipNamespaceName(pp_stringviewify(func)), func

#define reflect_class(cls)                                                  \
    static const std::string &class_name() noexcept                          \
    {                                                                       \
        static const std::string name = pp_stringify(cls);                  \
        return name;                                                        \
    }

    template <typename MapT, typename KeyT, typename Function>
    static inline constexpr bool getMember(MapT &&map, KeyT &&k, Function &&func) noexcept
    {
        return meta::find(std::forward<MapT>(map), std::forward<KeyT>(k), std::forward<Function>(func));
    }

    template <typename MapT, typename KeyT, typename Function>
    static inline constexpr bool getFunction(MapT &&map, KeyT &&k, Function &&func) noexcept
    {
        return getMember(std::forward<MapT>(map), std::forward<KeyT>(k), std::forward<Function>(func));
    }

    template <typename MemberPtrT, typename MapT, typename KeyT>
    static inline constexpr auto getMember(MapT &&map, KeyT &&k) noexcept
    {
        std::optional<MemberPtrT> result;
        auto visitor = shiva::meta::makeVisitor([&result]([[maybe_unused]] auto &&k, MemberPtrT v) {
            result = v;
        }, []([[maybe_unused]] auto &&k, [[maybe_unused]] auto &&v) {
        });

        getMember(std::forward<MapT>(map), std::forward<KeyT>(k), visitor);
        return result;
    }

    template <typename MemberPtrT, typename MapT, typename KeyT>
    static inline constexpr auto getFunction(MapT &&map, KeyT &&k) noexcept
    {
        return getMember<MemberPtrT>(std::forward<MapT>(map), std::forward<KeyT>(k));
    }

    class MemberNotFound : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Member not found";
        }
    };

    template <typename FunctionT, typename MapT, typename KeyT, typename Obj, typename ...Args>
    static inline constexpr auto callFunction(MapT &&map, KeyT &&k, Obj &&obj, Args &&...args)
    {
        using ObjRawType = std::decay_t<std::remove_pointer_t<std::decay_t<Obj>>>;
        using MemberFunctionT = FunctionT ObjRawType::*;
        auto memberOpt = getMember<MemberFunctionT>(std::forward<MapT>(map), std::forward<KeyT>(k));

        if (!memberOpt) {
            throw MemberNotFound();
        }
        return std::invoke(*memberOpt, obj, std::forward<Args>(args)...);
    }
}
