#!/bin/sh
../rshell << 'EOF'
echo hello | tr a-z A-Z
echo hello # | tr a-z A-Z
cat < ../test.txt | tr A-Z a-z | tee ../test2.txt | tr a-z A-Z > ../test3.txt
exit
EOF
