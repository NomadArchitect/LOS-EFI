gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms -ffreestanding -c efi_main.c -o efimain.o
gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms efimain.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efi_main -o BOOTX64.EFI

rem gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms -ffreestanding -Wl,--oformat=binary -e main -c loader/loader.c -o loader/loader.bin

gcc -Wall -Werror -m64 -std=c17 -DUNICODE -mabi=ms -Wl,--oformat=binary -Wl,--image-base -Wl,0x10000000 -e kmain -c loader/loader.c -o loader/loader.bin

del *.o

pause
