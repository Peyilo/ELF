//
// Created by Peyilo on 2025/3/3.
//

#include "elf64.h"
#include <stdlib.h>

void parse_elf64_header(Elf64_Ehdr *ehdr, FILE *file) {
    fseek(file, 0, SEEK_SET);
    if (fread(ehdr, sizeof(Elf64_Ehdr), 1, file) != 1) {
        perror("Failed to read ELF header");
        exit(-1);
    }
}

void print_elf64_header(Elf64_Ehdr *header) {
    // Print magic bytes
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    // Print class
    printf("  Class:                             ");
    if (header->e_ident[EI_CLASS] == ELFCLASS32) {
        printf("ELF32\n");
    } else if (header->e_ident[EI_CLASS] == ELFCLASS64) {
        printf("ELF64\n");
    } else {
        printf("Unknown\n");
    }

    // Print data encoding
    printf("  Data:                              ");
    if (header->e_ident[EI_DATA] == ELFDATA2LSB) {
        printf("2's complement, little endian\n");
    } else if (header->e_ident[EI_DATA] == ELFDATA2MSB) {
        printf("2's complement, big endian\n");
    } else {
        printf("Unknown\n");
    }

    // Print version
    printf("  Version:                           %u (current)\n", header->e_ident[EI_VERSION]);

    // Print OS/ABI
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
        default: printf("Unknown\n"); break;
    }

    // Print ABI version
    printf("  ABI Version:                       %u\n", header->e_ident[EI_ABIVERSION]);

    // Print type
    printf("  Type:                              ");
    switch (header->e_type) {
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN: printf("DYN (Shared object file)\n"); break;
        case ET_REL: printf("REL (Relocatable file)\n"); break;
        default: printf("Unknown\n"); break;
    }

    // Print machine type
    printf("  Machine:                           ");
    switch (header->e_machine) {
        case EM_386: printf("Intel 80386\n"); break;
        case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
        case EM_ARM: printf("ARM\n"); break;
        case EM_AARCH64: printf("AArch64\n"); break;
        default: printf("Unknown\n"); break;
    }

    // Print other information
    printf("  Version:                           0x%X\n", header->e_version);
    printf("  Entry point address:               0x%llX\n", header->e_entry);
    printf("  Start of program headers:          %llu (bytes into file)\n", header->e_phoff);
    printf("  Start of section headers:          %llu (bytes into file)\n", header->e_shoff);
    printf("  Flags:                             0x%X\n", header->e_flags);
    printf("  Size of this header:               %u (bytes)\n", header->e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", header->e_phentsize);
    printf("  Number of program headers:         %u\n", header->e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", header->e_shentsize);
    printf("  Number of section headers:         %u\n", header->e_shnum);
    printf("  Section header string table index: %u\n", header->e_shstrndx);
}