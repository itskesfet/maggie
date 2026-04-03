#!/bin/bash 

nasm -f elf64 deltav.s -o deltav.o
gcc deltav.o -o deltav -no-pie -lm

if [ $? -eq 0 ]; then
    echo "Build successful"
else
    echo "Build failed"
fi
