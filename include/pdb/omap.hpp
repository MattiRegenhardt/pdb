//
// Created by Matti on 01.03.2021.
//

#ifndef PDB_INCLUDE_PDB_OMAP_HPP
#define PDB_INCLUDE_PDB_OMAP_HPP

#include <cstdint>

namespace pdb
{
	class omap_t
	{
	public:
		omap_t() noexcept = default;
		omap_t(std::uint32_t source, std::uint32_t target) noexcept;

		[[nodiscard]]
		std::uint32_t source() const noexcept;
		[[nodiscard]]
		std::uint32_t target() const noexcept;

		[[nodiscard]]
		bool operator==(omap_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(omap_t const& rhs) const noexcept;

	private:
		std::uint32_t source_{ 0u };
		std::uint32_t target_{ 0u };
	};
}

#endif //PDB_INCLUDE_PDB_OMAP_HPP
