//
// Created by Matti on 28.02.2021.
//

#include <pdb/error.hpp>

namespace pdb
{
	static error_category g_ErrorCategory;

	char const* error_category::name() const noexcept
	{
		return "pdb";
	}
	std::string error_category::message(int ev) const
	{
		switch (static_cast<errc>(ev))
		{
		case errc::no_input: return "no input data provided";
		case errc::super_block_truncated: return "MSF super block truncated";
		case errc::invalid_super_block: return "invalid MSF super block magic";
		case errc::no_dbi_stream: return "no DBI stream found";
		case errc::dbi_optional_debug_header_truncated: return "DBI optional debug header data truncated";
		default: return {};
		}
	}

	[[nodiscard]]
	std::error_code make_error_code(errc e) noexcept
	{
		return { static_cast<std::int32_t>(e), g_ErrorCategory };
	}
}
