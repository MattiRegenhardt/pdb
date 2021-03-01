//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_DBI_HPP
#define PDB_INCLUDE_PDB_DBI_HPP

#include <array>
#include <optional>
#include "detail/dbi_header.hpp"
#include "symbol_stream.hpp"
#include "omap_stream.hpp"
#include "section_stream.hpp"
#include "error.hpp"

namespace pdb
{
	class pdb_t;

	class dbi_t
	{
	public:
		explicit dbi_t(pdb_t const* pdb_instance);

		bool parse(std::error_code& ec) noexcept;

		[[nodiscard]]
		std::uint32_t age() const noexcept;

		[[nodiscard]]
		symbol_stream_t const& symbol_stream() const noexcept;
		[[nodiscard]]
		std::optional<omap_stream_t> omap_to_src_stream() const noexcept;
		[[nodiscard]]
		std::optional<omap_stream_t> omap_from_src_stream() const noexcept;
		[[nodiscard]]
		std::optional<section_stream_t> section_stream() const noexcept;
		[[nodiscard]]
		std::optional<section_stream_t> original_section_stream() const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(dbi_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(dbi_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		detail::dbi_header_t dbi_header_{};
		std::array<std::uint16_t, 11u> optional_debug_header_{};
		std::size_t optional_debug_header_size_{ 0u };
		symbol_stream_t symbol_stream_{ pdb_ };
		std::optional<omap_stream_t> omap_to_src_;
		std::optional<omap_stream_t> omap_from_src_;
		std::optional<section_stream_t> section_stream_;
		std::optional<section_stream_t> original_section_stream_;
	};
}

#endif //PDB_INCLUDE_PDB_DBI_HPP
