//
// Created by Matti on 28.02.2021.
//

#include <pdb/symbol_iterator.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	symbol_iterator_t::symbol_iterator_t(pdb_t const* pdb_instance, std::uintptr_t stream_index, std::uintptr_t offset, detail::pubsym32_t const& rec) noexcept :
		symbol_{ pdb_instance, stream_index, offset, rec }
	{
	}

	[[nodiscard]]
	symbol_t const& symbol_iterator_t::operator*() const noexcept
	{
		return symbol_;
	}
	[[nodiscard]]
	symbol_t const* symbol_iterator_t::operator->() const noexcept
	{
		return &symbol_;
	}

	symbol_iterator_t& symbol_iterator_t::operator++() noexcept
	{
		auto const eof = symbol_.pdb_->msf().stream_size(symbol_.stream_);
		auto off = symbol_.offset_ + symbol_.symbol_data_.reclen + 2u;

		while (off < eof)
		{
			if (symbol_.symbol_data_.reclen == 0u)
			{
				break;
			}

			symbol_.pdb_->msf().read_stream(&symbol_.symbol_data_, sizeof(symbol_.symbol_data_), symbol_.stream_, off);

			if (static_cast<symbol_t::type>(symbol_.symbol_data_.rectyp) == symbol_t::type::pub32)
			{
				symbol_.offset_ = off;
				return *this;
			}

			off += symbol_.symbol_data_.reclen + 2u;
		}

		std::memset(&symbol_.symbol_data_, 0, sizeof(symbol_.symbol_data_));
		symbol_.offset_ = eof;

		return *this;
	}
	symbol_iterator_t symbol_iterator_t::operator++() const noexcept
	{
		auto temp = *this;
		++(*this);
		return temp;
	}

	[[nodiscard]]
	bool symbol_iterator_t::operator==(symbol_iterator_t const& rhs) const noexcept
	{
		return symbol_ == rhs.symbol_;
	}
	[[nodiscard]]
	bool symbol_iterator_t::operator!=(symbol_iterator_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
