//
// Created by Matti on 01.03.2021.
//

#ifndef PDB_INCLUDE_PDB_SECTION_HPP
#define PDB_INCLUDE_PDB_SECTION_HPP

#include <array>
#include <cstdint>
#include <string_view>

namespace pdb
{
	class section_t
	{
	public:
		[[nodiscard]]
		std::string_view const name() const noexcept;
		[[nodiscard]]
		std::uint32_t virtual_size() const noexcept;
		[[nodiscard]]
		std::uint32_t virtual_address() const noexcept;
		[[nodiscard]]
		std::uint32_t size_of_raw_data() const noexcept;
		[[nodiscard]]
		std::uint32_t pointer_to_raw_data() const noexcept;
		[[nodiscard]]
		std::uint32_t pointer_to_relocations() const noexcept;
		[[nodiscard]]
		std::uint32_t pointer_to_linenumbers() const noexcept;
		[[nodiscard]]
		std::uint32_t number_of_relocations() const noexcept;
		[[nodiscard]]
		std::uint32_t number_of_linenumbers() const noexcept;
		[[nodiscard]]
		std::uint32_t characteristics() const noexcept;

		[[nodiscard]]
		bool operator==(section_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(section_t const& rhs) const noexcept;

	private:
		std::array<char, 8u> name_{};
		std::uint32_t virtual_size_{};
		std::uint32_t virtual_address_{};
		std::uint32_t size_of_raw_data_{};
		std::uint32_t pointer_to_raw_data_{};
		std::uint32_t pointer_to_relocations_{};
		std::uint32_t pointer_to_linenumbers_{};
		std::uint16_t number_of_relocations_{};
		std::uint16_t number_of_linenumbers_{};
		std::uint32_t characteristics_{};
	};
}

#endif //PDB_INCLUDE_PDB_SECTION_HPP
