//
// Created by Matti on 28.02.2021.
//

#include <bit>
#include <cassert>
#include <pdb/msf.hpp>
#include <pdb/pdb.hpp>

namespace pdb
{
	msf_t::msf_t(pdb_t const* pdb_instance) noexcept :
		pdb_{ pdb_instance }
	{
		assert(pdb_);
	}

	bool msf_t::parse(std::error_code& ec) noexcept
	{
		assert(pdb_);
		std::memset(&super_block_, 0, sizeof(super_block_));

		if (!pdb_->data() || !pdb_->size())
		{
			ec = make_error_code(errc::no_input);
			return false;
		}

		if (pdb_->size() < sizeof(super_block_))
		{
			ec = make_error_code(errc::super_block_truncated);
			return false;
		}

		std::memcpy(&super_block_, pdb_->data(), sizeof(super_block_));

		if (!super_block_)
		{
			ec = make_error_code(errc::invalid_super_block);
			return false;
		}

		return true;
	}

	[[nodiscard]]
	std::size_t msf_t::block_size() const noexcept
	{
		return super_block_.block_size;
	}

	[[nodiscard]]
	std::size_t msf_t::stream_count() const noexcept
	{
		return get_stream_directory_index(0u);
	}
	[[nodiscard]]
	std::size_t msf_t::stream_size(std::uintptr_t stream_index) const noexcept
	{
		if (stream_count() <= stream_index)
		{
			return 0u;
		}

		return get_stream_directory_index(stream_index + 1u);
	}
	[[nodiscard]]
	std::size_t msf_t::stream_blocks(std::uintptr_t stream_index) const noexcept
	{
		return (stream_size(stream_index) + super_block_.block_size - 1u) / super_block_.block_size;
	}

	[[nodiscard]]
	std::uint8_t const* msf_t::stream_block(std::uintptr_t stream_index, std::uintptr_t block_index) const noexcept
	{
		auto const num_streams = stream_count();

		if (num_streams <= stream_index)
		{
			return nullptr;
		}

		if (get_stream_directory_index(stream_index + 1u) <= block_index)
		{
			return nullptr;
		}

		auto index = num_streams;

		for (auto i = 0u; i < stream_index; ++i)
		{
			index += (get_stream_directory_index(i + 1u) + super_block_.block_size - 1u) / super_block_.block_size;
		}

		auto const offset = get_stream_directory_index(index + block_index + 1u);
		return pdb_->data() + offset * super_block_.block_size;
	}

	std::size_t msf_t::read_stream(void* buffer, std::size_t size, std::uintptr_t stream_index, std::uintptr_t offset) const noexcept
	{
		auto const max_size = stream_size(stream_index);

		if (max_size == 0u)
		{
			return 0u;
		}

		size = std::min(size, max_size - offset);

		if (size == 0u)
		{
			return 0u;
		}

		auto block_index = offset / super_block_.block_size;
		auto block_offset = offset - block_index * super_block_.block_size;
		auto read = 0u;

		while (size != 0u)
		{
			auto const block_max_size = std::min(super_block_.block_size - block_offset, size);

			if (block_max_size == 0u)
			{
				break;
			}

			auto const* const block_ptr = stream_block(stream_index, block_index);

			if (!block_ptr)
			{
				break;
			}

			std::memcpy(static_cast<std::uint8_t*>(buffer) + read, block_ptr + block_offset, block_max_size);

			block_offset = 0u;
			++block_index;
			size -= block_max_size;
			read += block_max_size;
		}

		return read;
	}

	[[nodiscard]]
	bool msf_t::valid() const noexcept
	{
		return super_block_.valid();
	}

	[[nodiscard]]
	msf_t::operator bool() const noexcept
	{
		return valid();
	}

	[[nodiscard]]
	bool msf_t::operator==(msf_t const& rhs) const noexcept
	{
		return pdb_ == rhs.pdb_ && super_block_ == rhs.super_block_;
	}
	[[nodiscard]]
	bool msf_t::operator!=(msf_t const& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	[[nodiscard]]
	std::uint32_t msf_t::get_stream_directory_index(std::uintptr_t index) const noexcept
	{
		if (index * sizeof(std::uint32_t) >= super_block_.num_directory_bytes)
		{
			return 0u;
		}

		auto const byte_offset = index * sizeof(std::uint32_t);
		auto const directory_block = byte_offset / super_block_.block_size;
		auto const directory_index = (byte_offset - directory_block * super_block_.block_size) / sizeof(std::uint32_t);
		auto const* const directory_map = std::bit_cast<std::uint32_t const*>(pdb_->data() + super_block_.block_map_address * super_block_.block_size);
		auto const block_index = directory_map[directory_block];
		auto const* const block = std::bit_cast<std::uint32_t const*>(pdb_->data() + block_index * super_block_.block_size);
		return block[directory_index];
	}
}
