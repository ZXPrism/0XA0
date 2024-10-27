# Makefile for my operating system - 0xA0 - !

ALL : os.iso

ASM_KERNEL_FILES := $(shell find src/asm/kernel -name "*.s")
CPP_FILES := $(shell find src -name "*.cpp")
OBJ_FILES := $(patsubst src/%.s, obj/%.o, $(ASM_KERNEL_FILES)) $(patsubst src/%.cpp, obj/%.o, $(CPP_FILES))


CRTI_OBJ := obj/asm/runtime/crti.o
CRTN_OBJ := obj/asm/runtime/crtn.o


CC := i686-elf-g++
CFLAGS := -ffreestanding -O2 -Wall -Wextra -Werror -fno-exceptions -fno-rtti -nostdlib


CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)


obj/%.o : src/%.s
	mkdir -p $(dir $@)
	i686-elf-as $< -o $@


obj/%.o : src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -I src -c $< -o $@ $(CFLAGS)


OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJ_FILES) $(CRTEND_OBJ) $(CRTN_OBJ)


obj/os.bin : src/linker.ld $(OBJ_LINK_LIST)
	$(CC) -T src/linker.ld -o $@ $(OBJ_LINK_LIST) $(CFLAGS) -lgcc


os.iso : obj/os.bin src/grub.cfg
	mkdir -p iso/boot/grub
	cp obj/os.bin iso/boot/os.bin
	cp src/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

clean : 
	-rm -rf obj
	-rm -rf *.iso
	-rm -rf iso
	-rm -rf boot


.PHONY : clean ALL
