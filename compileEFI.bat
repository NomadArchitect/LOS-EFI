gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms -ffreestanding -c efi_main.c -o efimain.o
gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms efimain.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -Wl,--image-base -Wl,0x10000000 -e efi_main -o BOOTX64.EFI

del *.o

pause
