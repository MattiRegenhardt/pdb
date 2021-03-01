cmake_minimum_required(VERSION 3.19)
project(pdb CXX)

add_library(
		pdb
		STATIC
		src/dbi.cpp
		src/error.cpp
		src/msf.cpp
		src/omap.cpp
		src/omap_iterator.cpp
		src/omap_stream.cpp
		src/pdb.cpp
		src/section.cpp
		src/section_iterator.cpp
		src/section_stream.cpp
		src/symbol.cpp
		src/symbol_iterator.cpp
		src/symbol_stream.cpp
)
target_include_directories(
		pdb
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(
		pdb
		PUBLIC
		cxx_std_20
)

add_executable(
		pdb-dump-symbols
		example/dump-symbols.cpp
)
target_link_libraries(
		pdb-dump-symbols
		PRIVATE
		pdb
)
