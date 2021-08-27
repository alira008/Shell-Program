#!/bin/sh
../rshell << 'EOF'
[ -e ../src ]
[ -f ../src ]
[ -d ../src ]
exit
EOF
