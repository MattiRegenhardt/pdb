//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_SYMBOL_ITERATOR_HPP
#define PDB_INCLUDE_PDB_SYMBOL_ITERATOR_HPP

#include <cstdint>
#include "symbol.hpp"

namespace pdb
{
	class pdb_t;

	class symbol_iterator_t
	{
	public:
		symbol_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream_index, std::uintptr_t offset, detail::pubsym32_t const& rec) noexcept;

		[[nodiscard]]
		symbol_t const& operator*() const noexcept;
		[[nodiscard]]
		symbol_t const* operator->() const noexcept;

		symbol_iterator_t& operator++() noexcept;
		symbol_iterator_t operator++() const noexcept;

		[[nodiscard]]
		bool operator==(symbol_iterator_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(symbol_iterator_t const& rhs) const noexcept;

	private:
		symbol_t symbol_;
	};
}

#endif //PDB_INCLUDE_PDB_SYMBOL_ITERATOR_HPP
