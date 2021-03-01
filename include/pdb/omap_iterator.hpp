//
// Created by Matti on 01.03.2021.
//

#ifndef PDB_INCLUDE_PDB_OMAP_ITERATOR_HPP
#define PDB_INCLUDE_PDB_OMAP_ITERATOR_HPP

#include <cstdint>
#include "omap.hpp"

namespace pdb
{
	class pdb_t;

	class omap_iterator_t
	{
	public:
		omap_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream, std::uintptr_t offet, omap_t const& omap) noexcept;

		[[nodiscard]]
		omap_t const& operator*() const noexcept;
		[[nodiscard]]
		omap_t const* operator->() const noexcept;

		omap_iterator_t& operator++() noexcept;
		omap_iterator_t operator++() const noexcept;

		[[nodiscard]]
		bool operator==(omap_iterator_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(omap_iterator_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		std::uintptr_t stream_;
		std::uintptr_t offset_;
		omap_t omap_;
	};
}

#endif //PDB_INCLUDE_PDB_OMAP_ITERATOR_HPP
