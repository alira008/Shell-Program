#!/bin/sh
../rshell << 'EOF'
echo a && exit
ls ; exit
EOF

