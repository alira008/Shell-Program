#!/bin/sh
../rshell << 'EOF'
test -e ../name.txt
test -f ../name.txt
test -d ../name.txt
exit
EOF
