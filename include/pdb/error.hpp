//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_ERROR_HPP
#define PDB_INCLUDE_PDB_ERROR_HPP

#include <system_error>

namespace pdb
{
	enum class errc
	{
		no_input,
		super_block_truncated,
		invalid_super_block,
		no_dbi_stream,
		dbi_optional_debug_header_truncated
	};

	class error_category : public std::error_category
	{
	public:
		char const* name() const noexcept override;
		std::string message(int ev) const override;
	};

	[[nodiscard]]
	std::error_code make_error_code(errc e) noexcept;
}

namespace std
{
	template<>
	struct is_error_code_enum<pdb::errc> : std::true_type {};
}

#endif //PDB_INCLUDE_PDB_ERROR_HPP
