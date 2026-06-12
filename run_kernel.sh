echo "Starting kernel (qemu)"

qemu-system-riscv64 -machine virt -kernel build/kernel.elf -bios none -nographic