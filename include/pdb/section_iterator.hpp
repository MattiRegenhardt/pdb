//
// Created by Matti on 01.03.2021.
//

#ifndef PDB_INCLUDE_PDB_SECTION_ITERATOR_HPP
#define PDB_INCLUDE_PDB_SECTION_ITERATOR_HPP

#include <cstdint>
#include "section.hpp"

namespace pdb
{
	class pdb_t;

	class section_iterator_t
	{
	public:
		section_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream, std::uintptr_t offet, section_t const& section) noexcept;

		[[nodiscard]]
		section_t const& operator*() const noexcept;
		[[nodiscard]]
		section_t const* operator->() const noexcept;

		section_iterator_t& operator++() noexcept;
		section_iterator_t operator++() const noexcept;

		[[nodiscard]]
		bool operator==(section_iterator_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(section_iterator_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		std::uintptr_t stream_;
		std::uintptr_t offset_;
		section_t section_;
	};
}

#endif //PDB_INCLUDE_PDB_SECTION_ITERATOR_HPP
