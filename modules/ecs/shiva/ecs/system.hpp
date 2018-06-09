//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <shiva/ecs/base_system.hpp>
#include <shiva/ecs/details/system_type_traits.hpp>

namespace shiva::ecs
{
	template <typename SystemDerived, typename TSystemType>
	class system : public base_system
	{
		template <typename T>
		using is_kind_system = std::is_same<TSystemType, T>;
	public:
		template <typename ...Args>
		explicit system(Args&&...args) noexcept : base_system(std::forward<Args>(args)...)
		{
		}

		~system() noexcept override = default;

		static constexpr system_type get_system_type() noexcept
		{
			using is_same_list = meta::list::Transform<details::valid_systems_list, is_kind_system>;
			static_assert(details::is_valid_system_v(is_same_list{}),
				"valid_system_list is an invalid template parameter");
			if constexpr (std::is_same_v<TSystemType, system_logic_update>)
				return logic_update;
			else if constexpr (std::is_same_v<TSystemType, system_pre_update>)
				return pre_update;
			else if constexpr (std::is_same_v<TSystemType, system_post_update>)
				return post_update;
			return size;
		}

		//! Override functions
		void update() noexcept override = 0;

		const std::string& get_name() const noexcept final
		{
			return SystemDerived::class_name();
		}
	};
}
