#!/bin/bash

set -e

echo "Kernel Builder Ver 1.1.0"

mkdir -p build

echo "[1/4] Update Build Number"

current=$(grep -Eo 'build [0-9]+' README.md | grep -Eo '[0-9]+')
next=$((current + 1))

sed -i '' -E "s/build [0-9]+/build $next/" README.md

sed -i '' -E "s/#define S64_VER \"[0-9]+\"/#define S64_VER \"$next\"/" kernel/core/include/framework.h

echo "  -> Build Number: $next"

echo "[2/4] Compile Entry Assembly"

if ! riscv64-unknown-elf-as -o build/entry.o kernel/entry.s 2>build/error.log; then
    echo "Assembly compile failed:"
    cat build/error.log
    exit 1
fi

echo "[3/4] Compile C++ Sources"

objects=""
compile_db="["
first=true

while IFS= read -r file; do
    obj="build/$(basename "${file%.cpp}").o"

    echo "  -> $file"

    if ! riscv64-unknown-elf-g++ \
        -c "$file" \
        -o "$obj" \
        -mcmodel=medany \
        -Ikernel \
        2>build/error.log; then

        echo
        echo "Compilation failed:"
        cat build/error.log
        exit 1
    fi

    objects="$objects $obj"

    $first || compile_db="$compile_db,"
    first=false
    compile_db="$compile_db
  {
    \"directory\": \"$(pwd)\",
    \"command\": \"clang++ -c $file -o $obj -Ikernel\",
    \"file\": \"$file\"
  }"

done < <(find kernel -name "*.cpp")

compile_db="$compile_db
]"

echo "$compile_db" > compile_commands.json
echo "  -> compile_commands.json generated"

echo "[4/4] Link Kernel"

if ! riscv64-unknown-elf-ld \
    -o build/kernel.elf \
    -T kernel/kernel.ld \
    build/entry.o \
    $objects \
    2>build/error.log; then

    echo
    echo "Link failed:"
    cat build/error.log
    exit 1
fi
echo "Build Success!"