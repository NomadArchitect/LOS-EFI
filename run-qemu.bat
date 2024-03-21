qemu-system-x86_64 -rtc base=localtime -drive format=raw,unit=0,file=drive/drive.hdd -bios bios64.bin -m 256M -display sdl -vga std -name TESTOS -machine q35 -usb -device usb-mouse -device AC97

pause
