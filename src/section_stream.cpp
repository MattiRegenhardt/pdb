//
// Created by Matti on 01.03.2021.
//

#include <pdb/section_stream.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	section_stream_t::section_stream_t(pdb_t const* pdb_instance, std::uintptr_t stream_index) noexcept :
		pdb_{ pdb_instance },
		stream_{ stream_index }
	{
	}

	[[nodiscard]]
	std::uintptr_t section_stream_t::stream_index() const noexcept
	{
		return stream_;
	}

	[[nodiscard]]
	section_iterator_t section_stream_t::begin() const noexcept
	{
		return cbegin();
	}
	[[nodiscard]]
	section_iterator_t section_stream_t::end() const noexcept
	{
		return cend();
	}

	[[nodiscard]]
	section_iterator_t section_stream_t::cbegin() const noexcept
	{
		section_t section{};
		return pdb_->msf().read_stream(&section, sizeof(section), stream_, 0u) == sizeof(section) ? section_iterator_t{ pdb_, stream_, 0u, section } : cend();
	}
	[[nodiscard]]
	section_iterator_t section_stream_t::cend() const noexcept
	{
		return { pdb_, stream_, pdb_->msf().stream_size(stream_), section_t{} };
	}

	[[nodiscard]]
	bool section_stream_t::valid() const noexcept
	{
		return pdb_ != nullptr && stream_ != 0u;
	}

	[[nodiscard]]
	section_stream_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool section_stream_t::operator==(section_stream_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_;
	}
	[[nodiscard]]
	bool section_stream_t::operator!=(section_stream_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
