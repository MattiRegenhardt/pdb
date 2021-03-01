//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_PDB_HPP
#define PDB_INCLUDE_PDB_PDB_HPP

#include <cstdint>
#include "error.hpp"
#include "msf.hpp"
#include "dbi.hpp"

namespace pdb
{
	class pdb_t
	{
	public:
		bool parse(void const* data, std::size_t size, std::error_code& ec) noexcept;

		[[nodiscard]]
		std::uint8_t const* data() const noexcept;
		[[nodiscard]]
		std::size_t size() const noexcept;

		[[nodiscard]]
		msf_t const& msf() const noexcept;
		[[nodiscard]]
		dbi_t const& dbi() const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(pdb_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(pdb_t const& rhs) const noexcept;

	private:
		std::uint8_t const* data_{ nullptr };
		std::size_t size_{ 0u };
		msf_t msf_{ this };
		dbi_t dbi_{ this };
	};
}

#endif //PDB_INCLUDE_PDB_PDB_HPP
