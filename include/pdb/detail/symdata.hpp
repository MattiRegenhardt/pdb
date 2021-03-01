//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_DETAIL_SYMDATA_HPP
#define PDB_INCLUDE_PDB_DETAIL_SYMDATA_HPP

#include <cstdint>
#include <cstring>

namespace pdb::detail
{
#pragma pack(push, 1)
	struct pubsym32_t
	{
		std::uint16_t reclen{};
		std::uint16_t rectyp{};
		std::uint32_t pubsymflags{};
		std::uint32_t off{};
		std::uint16_t seg{};
		//char name[N];

		[[nodiscard]]
		bool operator==(pubsym32_t const& rhs) const noexcept
		{
			return !std::memcmp(this, &rhs, sizeof(pubsym32_t));
		}
		[[nodiscard]]
		bool operator!=(pubsym32_t const& rhs) const noexcept
		{
			return !(*this == rhs);
		}
	};
#pragma pack(pop)
}

#endif //PDB_INCLUDE_PDB_DETAIL_SYMDATA_HPP
