gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms -ffreestanding -c efi_main.c -o efimain.o

gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms efimain.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -Wl,--image-base -Wl,0x10000000 -e efi_main -o BOOTX64.EFI

gcc -Wall -Werror -m64 -std=c17 -mabi=ms -ffreestanding -Wl,--oformat=binary -Wno-unused-variable -Wno-unused-but-set-variable -e main -c loader/loader.c -o loader/loader.bin

@echo off
rem gcc -fPIC -O0 -Wall -Werror -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wconversion -Wstrict-prototypes -Wunsafe-loop-optimizations -fno-builtin -fno-stack-protector -std=c17 -DUNICODE -nostdlib -ffreestanding -m64 -Wl,--oformat=binary -Wno-unused-variable -Wno-unused-but-set-variable -e main -c loader/loader.c -o loader/loader.bin

del *.o
@echo on

pause
