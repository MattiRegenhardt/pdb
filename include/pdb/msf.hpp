//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_MSF_HPP
#define PDB_INCLUDE_PDB_MSF_HPP

#include "detail/super_block.hpp"
#include "error.hpp"

namespace pdb
{
	class pdb_t;

	class msf_t
	{
	public:
		explicit msf_t(pdb_t const* pdb_instance) noexcept;

		bool parse(std::error_code& ec) noexcept;

		[[nodiscard]]
		std::size_t block_size() const noexcept;

		[[nodiscard]]
		std::size_t stream_count() const noexcept;
		[[nodiscard]]
		std::size_t stream_size(std::uintptr_t stream_index) const noexcept;
		[[nodiscard]]
		std::size_t stream_blocks(std::uintptr_t stream_index) const noexcept;

		[[nodiscard]]
		std::uint8_t const* stream_block(std::uintptr_t stream_index, std::uintptr_t block_index) const noexcept;

		std::size_t read_stream(void* buffer, std::size_t size, std::uintptr_t stream_index, std::uintptr_t offset) const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(msf_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(msf_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_;
		detail::super_block_t super_block_;

		[[nodiscard]]
		std::uint32_t get_stream_directory_index(std::uintptr_t index) const noexcept;
	};
}

#endif //PDB_INCLUDE_PDB_MSF_HPP
