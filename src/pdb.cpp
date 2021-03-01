//
// Created by Matti on 28.02.2021.
//

#include <pdb/pdb.hpp>

namespace pdb
{
	bool pdb_t::parse(void const* data, std::size_t size, std::error_code& ec) noexcept
	{
		ec.clear();

		data_ = nullptr;
		size_ = 0u;

		if (!data || !size)
		{
			ec = make_error_code(errc::no_input);
			return false;
		}

		data_ = static_cast<std::uint8_t const*>(data);
		size_ = size;

		return msf_.parse(ec) && dbi_.parse(ec);
	}

	[[nodiscard]]
	std::uint8_t const* pdb_t::data() const noexcept
	{
		return data_;
	}
	[[nodiscard]]
	std::size_t pdb_t::size() const noexcept
	{
		return size_;
	}

	[[nodiscard]]
	msf_t const& pdb_t::msf() const noexcept
	{
		return msf_;
	}
	[[nodiscard]]
	dbi_t const& pdb_t::dbi() const noexcept
	{
		return dbi_;
	}

	[[nodiscard]]
	bool pdb_t::valid() const noexcept
	{
		return data_ != nullptr && size_ > 0u && msf_ && dbi_;
	}

	[[nodiscard]]
	pdb_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool pdb_t::operator==(pdb_t const& rhs) const noexcept
	{
		return data_ == rhs.data_ && size_ == rhs.size_ && msf_ == rhs.msf_ && dbi_ == rhs.dbi_;
	}
	[[nodiscard]]
	bool pdb_t::operator!=(pdb_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}
