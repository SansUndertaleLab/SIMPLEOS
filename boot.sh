export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "boot.asm" -f bin -o "bin/boot.bin"
nasm "kernel_entry.asm" -f elf -o "obj/kernel_entry.o"

i386-elf-gcc -ffreestanding -m32 -g -c "kernel.cpp" -o "obj/kernel.o"
nasm "zeroes.asm" -f bin -o "bin/zeroes.bin"

i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000 "obj/kernel_entry.o" "obj/kernel.o" --oformat binary

cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"

qemu-system-x86_64 -drive format=raw,file="bin/OS.bin",index=0,if=floppy,  -m 128M