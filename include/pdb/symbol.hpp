//
// Created by Matti on 28.02.2021.
//

#ifndef PDB_INCLUDE_PDB_SYMBOL_HPP
#define PDB_INCLUDE_PDB_SYMBOL_HPP

#include "detail/symdata.hpp"

namespace pdb
{
	class pdb_t;
	class symbol_iterator_t;

	class symbol_t
	{
		friend class symbol_iterator_t;
	public:
		enum class type : std::uint16_t
		{
			pub32 = 0x110e
		};

		symbol_t(pdb_t const *pdb_instance, std::uintptr_t stream, std::uintptr_t offset, detail::pubsym32_t const& rec) noexcept;

		std::size_t name(char* buffer, std::size_t max_size) const noexcept;

		[[nodiscard]]
		bool valid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator==(symbol_t const& rhs) const noexcept;
		[[nodiscard]]
		bool operator!=(symbol_t const& rhs) const noexcept;

	private:
		pdb_t const* pdb_{ nullptr };
		std::uintptr_t stream_{ 0u };
		std::uintptr_t offset_{ 0u };
		detail::pubsym32_t symbol_data_{};
	};
}

#endif //PDB_INCLUDE_PDB_SYMBOL_HPP
