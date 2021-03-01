//
// Created by Matti on 01.03.2021.
//

#include <pdb/section_iterator.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	section_iterator_t::section_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream, std::uintptr_t offset, section_t const& section) noexcept :
		pdb_{ pdb_instance },
		stream_{ stream },
		offset_{ offset },
		section_{ section }
	{
	}

	[[nodiscard]]
	section_t const& section_iterator_t::operator*() const noexcept
	{
		return section_;
	}
	[[nodiscard]]
	section_t const* section_iterator_t::operator->() const noexcept
	{
		return &section_;
	}

	section_iterator_t& section_iterator_t::operator++() noexcept
	{
		auto const eof = pdb_->msf().stream_size(stream_);
		auto const off = offset_ + sizeof(section_t);

		if (off >= eof)
		{
			offset_ = eof;
			std::memset(&section_, 0, sizeof(section_));
			return *this;
		}

		offset_ = off;
		pdb_->msf().read_stream(&section_, sizeof(section_), stream_, offset_);

		return *this;
	}
	section_iterator_t section_iterator_t::operator++() const noexcept
	{
		auto temp = *this;
		++(*this);
		return temp;
	}

	[[nodiscard]]
	bool section_iterator_t::operator==(section_iterator_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_ && offset_ == rhs.offset_ && section_ == rhs.section_;
	}
	[[nodiscard]]
	bool section_iterator_t::operator!=(section_iterator_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
