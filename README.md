# origin — a custom x86 operating system

A hobby operating system written from scratch in C and x86 assembly, built to understand how a computer actually boots and runs — from the bootloader up through interrupts, virtual memory, and system calls.

Built and tested in QEMU (`qemu-system-i386`), booted via GRUB.

## Features

- **Custom cross-compiler toolchain** — `i686-elf-gcc`/`binutils` built from source, targeting a freestanding environment
- **GRUB/Multiboot bootloader** — boots as a standard bootable ISO, no custom boot sector required
- **VGA text-mode driver** — cursor tracking, newline handling, line-wrapping, backspace
- **Interrupt-driven I/O** — hand-built Interrupt Descriptor Table (IDT), PIC remapping, ISR wrappers
  - Keyboard input (scancode-to-ASCII translation, command buffer with echo)
  - PIT-driven timer interrupt (live seconds counter)
- **CPU exception handling** — handlers for Divide by Zero, Overflow, Bound Range Exceeded, Invalid Opcode, General Protection Fault, and Page Fault (with `CR2`-based faulting-address diagnostics), so the kernel reports a clean message and halts instead of triple-faulting into a reboot loop
- **Virtual memory** — two-level paging with an identity-mapped page table
- **Physical memory manager** — bitmap-based page allocator (`alloc_page` / `free_page`)
- **Kernel heap allocator** — First-Fit `kmalloc` / `kfree` over a linked list of blocks, backed by the physical memory manager
- **System call interface** — Linux-style syscalls (`write`, `read`, `exit`, `getpid`, `yield`, `sleep`) dispatched through `int 0x80`, using the classic EAX/EBX register convention
- **In-progress: round-robin scheduling** — per-task stacks, manual context switching via `pusha`/`popa` and stack-pointer swapping; task creation and the switch mechanism are implemented, with an open bug in the very first context switch still being debugged



## Project structure 
 
```text
boot/                bootloader entry point (boot.asm), linker script 
kernel/              kernel entry, IDT, ISRs, exceptions, syscalls, timer 
devices/             port I/O, PIT, keyboard/device drivers 
memory_management/   paging, physical memory manager, kernel heap 
task_management/     task struct, scheduler, context switching (WIP) 
isodir/              GRUB ISO staging directory 
```
## Building and running

Requires a `i686-elf` cross-compiler (`gcc`/`binutils`), `nasm`, `grub-mkrescue`, `xorriso`, and `qemu-system-i386`.

```bash
# compile each source file
i686-elf-gcc -c <file>.c -o <file>.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra \ -Ikernel -Idevices -Imemory_management -Itask_management nasm -f elf32 <file>.asm -o <file>.o

# link
i686-elf-gcc -T boot/linker.ld -o origin.bin -ffreestanding -O2 -nostdlib \ boot.o kernel.o port.o idt.o devices.o isr.o paging.o \ physical_memory_manager.o heap.o pit.o timer.o task.o exceptions.o system_call.o -lgcc

# build the bootable ISO
cp origin.bin isodir/boot/origin.bin
grub-mkrescue -o origin.iso isodir

# run
qemu-system-i386 -cdrom origin.iso
```

For debugging exceptions/crashes, QEMU's interrupt log is useful:

```bash
qemu-system-i386 -cdrom origin.iso -d int -no-reboot -no-shutdown
 ```

## Why this project

Built to understand OS internals at the level real systems work at — not through a tutorial abstraction, but by writing and debugging the actual bootloader, interrupt handlers, memory manager, and syscall layer, and tracing real crashes (page faults, general protection faults, triple faults) back to their root cause in the code.

## License

## Mit
