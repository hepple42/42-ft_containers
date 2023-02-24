#!/bin/bash

# Use Makefile to create two binaries using either the std or the ft containers
make re -s

# Run both binaries and write the output to the corresponding txt file
./std > std.txt
./ft > ft.txt

# Run diff command to find potential differences in the output and save results
diff std.txt ft.txt > result.diff
diff std.txt ft.txt
