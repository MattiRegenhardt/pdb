//
// Created by Matti on 01.03.2021.
//

#ifndef PDB_INCLUDE_PDB_OMAP_STREAM_HPP
#define PDB_INCLUDE_PDB_OMAP_STREAM_HPP

#include <cstdint>
#include "omap_iterator.hpp"

namespace pdb
{
	class pdb_t;

	class omap_stream_t
	{
	public:
		omap_stream_t(pdb_t const* pdb_instance, std::uintptr_t stream_index) noexcept;

		[[nodiscard]]
		std::uintptr_t stream_index() const noexcept;

		[[nodiscard]]
		omap_iterator_t begin() const noexcept;
		[[nodiscard]]
		omap_iterator_t end() const noexcept;

		[[nodiscard]]
		omap_iterator_t cbegin() const noexcept;
		[[nodiscard]]
		omap_iterator_t cend() const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(omap_stream_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(omap_stream_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		std::uintptr_t stream_;
	};
}

#endif //PDB_INCLUDE_PDB_OMAP_STREAM_HPP
