//
// Created by Matti on 28.02.2021.
//

#include <cassert>
#include <pdb/dbi.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	dbi_t::dbi_t(pdb_t const* pdb_instance) :
		pdb_{ pdb_instance }
	{
		assert(pdb_);
	}

	bool dbi_t::parse(std::error_code& ec) noexcept
	{
		std::memset(&dbi_header_, 0, sizeof(dbi_header_));
		std::memset(std::data(optional_debug_header_), 0, std::size(optional_debug_header_) * sizeof(std::uint16_t));
		optional_debug_header_size_ = 0u;

		if (pdb_->msf().read_stream(&dbi_header_, sizeof(dbi_header_), 3u, 0u) != sizeof(dbi_header_))
		{
			ec = make_error_code(errc::no_dbi_stream);
			return false;
		}

		optional_debug_header_size_ = std::min(std::size(optional_debug_header_), dbi_header_.optional_dbg_header_size / sizeof(std::uint16_t));

		if (optional_debug_header_size_ > 0u)
		{
			if (pdb_->msf()
					.read_stream(
							std::data(optional_debug_header_), optional_debug_header_size_ * sizeof(std::uint16_t), 3u,
							sizeof(dbi_header_) + dbi_header_.mod_info_size + dbi_header_.section_contribution_size + dbi_header_.section_map_size + dbi_header_.source_info_size +
							dbi_header_.type_server_map_size + dbi_header_.ec_substream_size
					) != optional_debug_header_size_ * sizeof(std::uint16_t))
			{
				ec = make_error_code(errc::dbi_optional_debug_header_truncated);
				return false;
			}

			if (optional_debug_header_size_ > 3u && optional_debug_header_[3u] != 65535 && optional_debug_header_[3u] != 0u)
			{
				omap_to_src_.emplace(pdb_, optional_debug_header_[3u]);
			}
			if (optional_debug_header_size_ > 4u && optional_debug_header_[4u] != 65535 && optional_debug_header_[4u] != 0u)
			{
				omap_from_src_.emplace(pdb_, optional_debug_header_[4u]);
			}
			if (optional_debug_header_size_ > 5u && optional_debug_header_[5u] != 65535 && optional_debug_header_[5u] != 0u)
			{
				section_stream_.emplace(pdb_, optional_debug_header_[5u]);
			}
			if (optional_debug_header_size_ > 10u && optional_debug_header_[10u] != 65535 && optional_debug_header_[10u] != 0u)
			{
				original_section_stream_.emplace(pdb_, optional_debug_header_[10u]);
			}
		}

		return symbol_stream_.parse(dbi_header_.sym_record_stream, ec);
	}

	[[nodiscard]]
	std::uint32_t dbi_t::age() const noexcept
	{
		return dbi_header_.age;
	}

	[[nodiscard]]
	symbol_stream_t const& dbi_t::symbol_stream() const noexcept
	{
		return symbol_stream_;
	}
	[[nodiscard]]
	std::optional<omap_stream_t> dbi_t::omap_to_src_stream() const noexcept
	{
		return omap_to_src_;
	}
	[[nodiscard]]
	std::optional<omap_stream_t> dbi_t::omap_from_src_stream() const noexcept
	{
		return omap_from_src_;
	}
	[[nodiscard]]
	std::optional<section_stream_t> dbi_t::section_stream() const noexcept
	{
		return section_stream_;
	}
	[[nodiscard]]
	std::optional<section_stream_t> dbi_t::original_section_stream() const noexcept
	{
		return original_section_stream_;
	}

	[[nodiscard]]
	bool dbi_t::valid() const noexcept
	{
		return symbol_stream_.valid();
	}

	[[nodiscard]]
	dbi_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool dbi_t::operator==(dbi_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && dbi_header_ == rhs.dbi_header_ && optional_debug_header_ == rhs.optional_debug_header_ && optional_debug_header_size_ == rhs.optional_debug_header_size_ && symbol_stream_ == rhs.symbol_stream_ && omap_to_src_ == rhs.omap_to_src_ && omap_from_src_ == rhs.omap_from_src_ && section_stream_ == rhs.section_stream_ && original_section_stream_ == rhs.original_section_stream_;
	}
	[[nodiscard]]
	bool dbi_t::operator!=(dbi_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
