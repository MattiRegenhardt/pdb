//
// Created by Matti on 01.03.2021.
//

#include <pdb/omap.hpp>

namespace pdb
{
	omap_t::omap_t(std::uint32_t source, std::uint32_t target) noexcept :
		source_{ source },
		target_{ target }
	{
	}

	[[nodiscard]]
	std::uint32_t omap_t::source() const noexcept
	{
		return source_;
	}
	[[nodiscard]]
	std::uint32_t omap_t::target() const noexcept
	{
		return target_;
	}

	[[nodiscard]]
	bool omap_t::operator==(omap_t const& rhs) const noexcept
	{
		return source_ == rhs.source_ && target_ == rhs.target_;
	}
	[[nodiscard]]
	bool omap_t::operator!=(omap_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
