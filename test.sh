#!/bin/bash

make -s

./std > std.txt
./ft > ft.txt

diff std.txt ft.txt > result.diff
diff std.txt ft.txt
