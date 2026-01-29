CC = gcc
AS = nasm

CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -Wall -Wextra
LDFLAGS = -m32 -T kernel/linker.ld -nostdlib -no-pie

OBJ = boot/boot.o kernel/kernel.o kernel/ui.o kernel/keyboard.o \
      kernel/auth.o kernel/main.o kernel/process.o \
      kernel/scheduler.o kernel/priority.o \
      kernel/timer.o kernel/log.o kernel/ipc.o \
      kernel/shell.o kernel/sync.o

all: os.bin

boot/boot.o:
	$(AS) -f elf32 boot/boot.asm -o boot/boot.o

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

os.bin: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o os.bin

clean:
	rm -f boot/*.o kernel/*.o os.bin

