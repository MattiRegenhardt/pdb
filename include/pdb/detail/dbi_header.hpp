//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_DETAIL_DBI_HEADER_HPP
#define PDB_INCLUDE_PDB_DETAIL_DBI_HEADER_HPP

#include <cstdint>

namespace pdb::detail
{
#pragma pack(push, 1)
	struct dbi_header_t
	{
		std::int32_t version_signature{};
		std::uint32_t version_header{};
		std::uint32_t age{};
		std::uint16_t global_stream_index{};
		std::uint16_t build_number{};
		std::uint16_t public_stream_index{};
		std::uint16_t pdb_dll_version{};
		std::uint16_t sym_record_stream{};
		std::uint16_t pdb_dll_rbld{};
		std::int32_t mod_info_size{};
		std::int32_t section_contribution_size{};
		std::int32_t section_map_size{};
		std::int32_t source_info_size{};
		std::int32_t type_server_map_size{};
		std::uint32_t mfc_type_server_index{};
		std::int32_t optional_dbg_header_size{};
		std::int32_t ec_substream_size{};
		std::uint16_t flags{};
		std::uint16_t machine{};
		std::uint32_t padding{};

		[[nodiscard]]
		bool operator==(dbi_header_t const& rhs) const noexcept
		{
			return !std::memcmp(this, &rhs, sizeof(dbi_header_t));
		}
		[[nodiscard]]
		bool operator!=(dbi_header_t const& rhs) const noexcept
		{
			return !(*this == rhs);
		}
	};
#pragma pack(pop)
}

#endif //PDB_INCLUDE_PDB_DETAIL_DBI_HEADER_HPP
