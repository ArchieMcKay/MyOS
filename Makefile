CFLAGS?=-O2 -g
CFLAGS:=$(CFLAGS) -Wall -Wextra


SRC_DIR=src
OBJ_DIR=obj
ISO_DIR=isodir
BOOT_DIR=isodir/boot

boot: $(SRC_DIR)/boot.S
	i686-elf-as $(SRC_DIR)/boot.S -o $(OBJ_DIR)/boot.o

bin: boot $(SRC_DIR)/kernel.c
	i686-elf-gcc -c $(SRC_DIR)/kernel.c -o $(OBJ_DIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

kernel: boot bin $(SRC_DIR)/linker.ld
	i686-elf-gcc -T $(SRC_DIR)/linker.ld -o $(BOOT_DIR)/myos.bin -ffreestanding -O2 -nostdlib $(OBJ_DIR)/boot.o $(OBJ_DIR)/kernel.o -lgcc

iso: kernel
	grub-mkrescue -o myos.iso $(ISO_DIR)

test: iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf $(OBJ_DIR)/* $(BOOT_DIR)/myos.bin myos.iso
