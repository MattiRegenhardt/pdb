//
// Created by Matti on 01.03.2021.
//

#include <pdb/omap_iterator.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	omap_iterator_t::omap_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream, std::uintptr_t offset, omap_t const& omap) noexcept :
		pdb_{ pdb_instance },
		stream_{ stream },
		offset_{ offset },
		omap_{ omap }
	{
	}

	[[nodiscard]]
	omap_t const& omap_iterator_t::operator*() const noexcept
	{
		return omap_;
	}
	[[nodiscard]]
	omap_t const* omap_iterator_t::operator->() const noexcept
	{
		return &omap_;
	}

	omap_iterator_t& omap_iterator_t::operator++() noexcept
	{
		auto const eof = pdb_->msf().stream_size(stream_);
		auto const off = offset_ + sizeof(omap_t);

		if (off >= eof)
		{
			offset_ = eof;
			std::memset(&omap_, 0, sizeof(omap_));
			return *this;
		}

		offset_ = off;
		pdb_->msf().read_stream(&omap_, sizeof(omap_), stream_, offset_);

		return *this;
	}
	omap_iterator_t omap_iterator_t::operator++() const noexcept
	{
		auto temp = *this;
		++(*this);
		return temp;
	}

	[[nodiscard]]
	bool omap_iterator_t::operator==(omap_iterator_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_ && offset_ == rhs.offset_ && omap_ == rhs.omap_;
	}
	[[nodiscard]]
	bool omap_iterator_t::operator!=(omap_iterator_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
