//
// Created by Matti on 28.02.2021.
//

#include <iostream>
#include <cstdint>
#include <fstream>
#include <memory>
#include <pdb/pdb.hpp>

std::int32_t main(std::int32_t argc, char const* argv[])
{
	for (auto i = 1; i < argc; ++i)
	{
		std::ifstream in{ argv[i], std::ifstream::in | std::ifstream::binary | std::ifstream::ate };

		if (!in)
		{
			std::cerr << "Can't open input \"" << argv[i] << "\"!\n";
			continue;
		}

		std::size_t size = in.tellg();

		if (size == 0u)
		{
			std::cerr << "Input \"" << argv[i] << "\" is empty!\n";
			continue;
		}

		in.seekg(0, std::ifstream::beg);

		auto const buffer = std::make_unique<std::uint8_t[]>(size);

		if (!buffer)
		{
			std::cerr << "Can't allocate " << size << " bytes for input \"" << argv[i] << "\"!\n";
			continue;
		}

		in.read(reinterpret_cast<char*>(buffer.get()), size);
		in.close();

		pdb::pdb_t p;
		std::error_code ec;

		std::cin.get();

		if (!p.parse(buffer.get(), size, ec))
		{
			std::cerr << "Can't parse input \"" << argv[i] << "\": " << ec.message() << '\n';
			continue;
		}

		std::cout << "Block Size: " << p.msf().block_size() << '\n';
		std::cout << "Age: " << p.dbi().age() << '\n';

		std::array<char, 1024u> symname{};

		std::cout << "Symbols:\n";

		for (auto const& sym : p.dbi().symbol_stream())
		{
			sym.name(std::data(symname), std::size(symname));
			symname[std::size(symname) - 1u] = '\0';

			std::cout << std::data(symname) << '\n';
		}

		if (p.dbi().omap_to_src_stream())
		{
			std::cout << "OMap to source:\n";
			auto omap_stream = p.dbi().omap_to_src_stream().value();

			for (auto const& omap : omap_stream)
			{
				std::cout << omap.source() << " -> " << omap.target() << '\n';
			}
		}

		if (p.dbi().omap_to_src_stream())
		{
			std::cout << "OMap from source:\n";
			auto omap_stream = p.dbi().omap_from_src_stream().value();

			for (auto const& omap : omap_stream)
			{
				std::cout << omap.source() << " -> " << omap.target() << '\n';
			}
		}

		if (p.dbi().section_stream())
		{
			std::cout << "Sections:\n";
			auto section_stream = p.dbi().section_stream().value();

			for (auto const& section : section_stream)
			{
				std::cout << section.name() << '\n';
			}
		}

		if (p.dbi().original_section_stream())
		{
			std::cout << "Original Sections:\n";
			auto section_stream = p.dbi().original_section_stream().value();

			for (auto const& section : section_stream)
			{
				std::cout << section.name() << '\n';
			}
		}
	}

	return 0;
}
