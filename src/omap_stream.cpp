//
// Created by Matti on 01.03.2021.
//

#include <pdb/omap_stream.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	omap_stream_t::omap_stream_t(pdb_t const* pdb_instance, std::uintptr_t stream_index) noexcept :
		pdb_{ pdb_instance },
		stream_{ stream_index }
	{
	}

	[[nodiscard]]
	std::uintptr_t omap_stream_t::stream_index() const noexcept
	{
		return stream_;
	}

	[[nodiscard]]
	omap_iterator_t omap_stream_t::begin() const noexcept
	{
		return cbegin();
	}
	[[nodiscard]]
	omap_iterator_t omap_stream_t::end() const noexcept
	{
		return cend();
	}

	[[nodiscard]]
	omap_iterator_t omap_stream_t::cbegin() const noexcept
	{
		omap_t omap{};
		return pdb_->msf().read_stream(&omap, sizeof(omap), stream_, 0u) == sizeof(omap) ? omap_iterator_t{ pdb_, stream_, 0u, omap } : cend();
	}
	[[nodiscard]]
	omap_iterator_t omap_stream_t::cend() const noexcept
	{
		return { pdb_, stream_, pdb_->msf().stream_size(stream_), omap_t{} };
	}

	[[nodiscard]]
	bool omap_stream_t::valid() const noexcept
	{
		return pdb_ != nullptr && stream_ != 0u;
	}

	[[nodiscard]]
	omap_stream_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool omap_stream_t::operator==(omap_stream_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_;
	}
	[[nodiscard]]
	bool omap_stream_t::operator!=(omap_stream_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
