//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_SYMBOL_STREAM_HPP
#define PDB_INCLUDE_PDB_SYMBOL_STREAM_HPP

#include "symbol_iterator.hpp"
#include "error.hpp"

namespace pdb
{
	class pdb_t;

	class symbol_stream_t
	{
	public:
		symbol_stream_t(pdb_t const* pdb_instance) noexcept;

		bool parse(std::uintptr_t stream_index, std::error_code& ec) noexcept;

		[[nodiscard]]
		std::uintptr_t stream_index() const noexcept;

		[[nodiscard]]
		symbol_iterator_t begin() const noexcept;
		[[nodiscard]]
		symbol_iterator_t end() const noexcept;

		[[nodiscard]]
		symbol_iterator_t cbegin() const noexcept;
		[[nodiscard]]
		symbol_iterator_t cend() const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(symbol_stream_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(symbol_stream_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		std::uintptr_t stream_{ 0u };
	};
}

#endif //PDB_INCLUDE_PDB_SYMBOL_STREAM_HPP
