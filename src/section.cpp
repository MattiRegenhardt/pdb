//
// Created by Matti on 01.03.2021.
//

#include <pdb/section.hpp>

namespace pdb
{
	[[nodiscard]]
	std::string_view const section_t::name() const noexcept
	{
		auto const len = [](char const* p, std::size_t n)
		{
			std::size_t r = 0u;

			for (; r <= n && p[r] != '\0'; ++r)
				;

			return r;
		};

		return { std::data(name_), len(std::data(name_), std::size(name_)) };
	}
	[[nodiscard]]
	std::uint32_t section_t::virtual_size() const noexcept
	{
		return virtual_size_;
	}
	[[nodiscard]]
	std::uint32_t section_t::virtual_address() const noexcept
	{
		return virtual_address_;
	}
	[[nodiscard]]
	std::uint32_t section_t::size_of_raw_data() const noexcept
	{
		return size_of_raw_data_;
	}
	[[nodiscard]]
	std::uint32_t section_t::pointer_to_raw_data() const noexcept
	{
		return pointer_to_raw_data_;
	}
	[[nodiscard]]
	std::uint32_t section_t::pointer_to_relocations() const noexcept
	{
		return pointer_to_relocations_;
	}
	[[nodiscard]]
	std::uint32_t section_t::pointer_to_linenumbers() const noexcept
	{
		return pointer_to_linenumbers_;
	}
	[[nodiscard]]
	std::uint32_t section_t::number_of_relocations() const noexcept
	{
		return number_of_relocations_;
	}
	[[nodiscard]]
	std::uint32_t section_t::number_of_linenumbers() const noexcept
	{
		return number_of_linenumbers_;
	}
	[[nodiscard]]
	std::uint32_t section_t::characteristics() const noexcept
	{
		return characteristics_;
	}

	[[nodiscard]]
	bool section_t::operator==(section_t const& rhs) const noexcept
	{
		return !std::memcmp(std::data(name_), std::data(rhs.name_), std::size(name_)) &&
		virtual_size_ == rhs.virtual_size_ && virtual_address_ == rhs.virtual_address_ &&
		size_of_raw_data_ == rhs.size_of_raw_data_ && pointer_to_raw_data_ == rhs.pointer_to_raw_data_ &&
		pointer_to_relocations_ == rhs.pointer_to_relocations_ && pointer_to_linenumbers_ == rhs.pointer_to_linenumbers_ &&
		number_of_relocations_ == rhs.number_of_relocations_ && number_of_linenumbers_ == rhs.number_of_linenumbers_ &&
		characteristics_ == rhs.characteristics_;

	}
	[[nodiscard]]
	bool section_t::operator!=(section_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
