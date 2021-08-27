#!/bin/sh
../rshell << 'EOF'
echo hello world # ; echo try again
echo a && echo b #&& echo c
exit
EOF
