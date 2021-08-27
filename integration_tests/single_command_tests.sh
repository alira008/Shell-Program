#!/bin/sh
../rshell << 'EOF'
echo a
echo b
ls
mkdir temp
ls
rm -rf temp
ls
exit
EOF
