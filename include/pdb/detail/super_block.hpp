//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_DETAIL_SUPER_BLOCK_HPP
#define PDB_INCLUDE_PDB_DETAIL_SUPER_BLOCK_HPP

#include <cstdint>
#include <array>

namespace pdb::detail
{
#pragma pack(push, 1)

	struct super_block_t
	{
		static constexpr std::array<std::uint8_t, 32u> Magic[] = {
				0x4Du, 0x69u, 0x63u, 0x72u, 0x6Fu, 0x73u, 0x6Fu, 0x66u,
				0x74u, 0x20u, 0x43u, 0x2Fu, 0x43u, 0x2Bu, 0x2Bu, 0x20u,
				0x4Du, 0x53u, 0x46u, 0x20u, 0x37u, 0x2Eu, 0x30u, 0x30u,
				0x0Du, 0x0Au, 0x1Au, 0x44u, 0x53u, 0x00u, 0x00u, 0x00u
		};

		std::array<std::uint8_t, 32u> magic{};
		std::uint32_t                 block_size{};
		std::uint32_t                 free_block_map_block{};
		std::uint32_t                 num_blocks{};
		std::uint32_t                 num_directory_bytes{};
		std::uint32_t                 unknown{};
		std::uint32_t                 block_map_address{};

		[[nodiscard]]
		bool valid() const noexcept
		{
			return !std::memcmp(std::data(magic), std::data(Magic), std::size(Magic));
		}

		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return valid();
		}

		[[nodiscard]]
		bool operator==(super_block_t const& rhs) const noexcept
		{
			return !std::memcmp(this, &rhs, sizeof(super_block_t));
		}
		[[nodiscard]]
		bool operator!=(super_block_t const& rhs) const noexcept
		{
			return !(*this == rhs);
		}
	};

#pragma pack(pop)
}

#endif //PDB_INCLUDE_PDB_DETAIL_SUPER_BLOCK_HPP
