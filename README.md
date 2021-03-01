# pdb
Simple C++ Microsoft PDB parsing library to extract symbols.

This library is a learning project and NOT production ready AT ALL.
The goal was to extract symbols and their corresponding RVAs from Microsoft's PDB files,
without doing any allocations besides actually loading the file into memory to combat memory fragmentation.
