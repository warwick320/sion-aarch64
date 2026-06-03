#!/bin/bash
echo "Kernel Builder Ver 1.0.0 (Only tested on apple silicone)"

echo "Compile Entry Assembly"
riscv64-unknown-elf-as -o build/entry.o kernel/entry.s
echo "Compile Kernel link script"
riscv64-unknown-elf-ld -o build/kernel.elf -T kernel/kernel.ld build/entry.o
echo "Update README file"

current=$(grep -Eo 'build [0-9]+' README.md | grep -Eo '[0-9]+')
next=$((current + 1))
sed -i '' -E "s/build [0-9]+/build $next/" README.md

echo "All process done. :>"