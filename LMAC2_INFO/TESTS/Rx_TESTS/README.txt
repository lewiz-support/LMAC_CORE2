
At this level are test cases done in ModelSim
Their scripts use MEM LOAD to load test information into memory models in the Verilog models

VIVADO directory contains tests which were done in Vivado simulator
Their scripts do not use MEM LOAD command (not available) so modification of
the READMEMH function is required to point to the correct memory data/ctrl files.