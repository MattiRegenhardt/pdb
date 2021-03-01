//
// Created by Matti on 28.02.2021.
//

#include <pdb/symbol_stream.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	symbol_stream_t::symbol_stream_t(pdb_t const* pdb_instance) noexcept :
		pdb_{ pdb_instance }
	{
	}

	bool symbol_stream_t::parse(std::uintptr_t stream_index, std::error_code& ec) noexcept
	{
		ec.clear();
		stream_ = stream_index;
		return true;
	}

	[[nodiscard]]
	std::uintptr_t symbol_stream_t::stream_index() const noexcept
	{
		return stream_;
	}

	[[nodiscard]]
	symbol_iterator_t symbol_stream_t::begin() const noexcept
	{
		return cbegin();
	}
	[[nodiscard]]
	symbol_iterator_t symbol_stream_t::end() const noexcept
	{
		return cend();
	}

	[[nodiscard]]
	symbol_iterator_t symbol_stream_t::cbegin() const noexcept
	{
		detail::pubsym32_t rec{};
		return pdb_->msf().read_stream(&rec, sizeof(rec), stream_, 0u) == sizeof(rec) ? symbol_iterator_t{ pdb_, stream_, 0u, rec } : cend();
	}
	[[nodiscard]]
	symbol_iterator_t symbol_stream_t::cend() const noexcept
	{
		return { pdb_, stream_, pdb_->msf().stream_size(stream_), detail::pubsym32_t{} };
	}

	[[nodiscard]]
	bool symbol_stream_t::valid() const noexcept
	{
		return true;
	}

	[[nodiscard]]
	symbol_stream_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool symbol_stream_t::operator==(symbol_stream_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_;
	}
	[[nodiscard]]
	bool symbol_stream_t::operator!=(symbol_stream_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
