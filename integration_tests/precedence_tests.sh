#!/bin/sh
../rshell << 'EOF'
echo A && echo B || echo C && echo D
(echo A && echo B) || (echo C && echo D)
exit
EOF
