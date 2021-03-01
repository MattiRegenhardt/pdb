//
// Created by Matti on 01.03.2021.
//

#include <pdb/symbol.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	symbol_t::symbol_t(pdb_t const *pdb_instance, std::uintptr_t stream, std::uintptr_t offset, detail::pubsym32_t const& rec) noexcept :
		pdb_{ pdb_instance },
		stream_{ stream },
		offset_{ offset },
		symbol_data_{ rec }
	{
	}

	std::size_t symbol_t::name(char* buffer, std::size_t max_size) const noexcept
	{
		auto const name_length = symbol_data_.reclen - sizeof(symbol_data_);
		auto const len = std::min(max_size, name_length);
		pdb_->msf().read_stream(buffer, len, stream_, offset_ + sizeof(symbol_data_));
		return name_length;
	}

	[[nodiscard]]
	bool symbol_t::valid() const noexcept
	{
		return pdb_ != nullptr && stream_ != 0u;
	}

	[[nodiscard]]
	symbol_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool symbol_t::operator==(symbol_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && stream_ == rhs.stream_ && offset_ == rhs.offset_ && symbol_data_ == rhs.symbol_data_;
	}
	[[nodiscard]]
	bool symbol_t::operator!=(symbol_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
