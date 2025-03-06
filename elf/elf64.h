//
// Created by Peyilo on 2025/3/3.
//

#ifndef ELF_ELF64_H
#define ELF_ELF64_H

#include <stdint.h>
#include <stdio.h>
#include "elf_constants.h"

typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef uint32_t Elf64_Word;
typedef int32_t  Elf64_Sword;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

typedef struct
{
    unsigned char e_ident[16];          // ELF identification
    Elf64_Half e_type;                  // Object file type
    Elf64_Half e_machine;               // Machine type
    Elf64_Word e_version;               // Object file version
    Elf64_Addr e_entry;                 // Entry point address
    Elf64_Off e_phoff;                  // Program header offset
    Elf64_Off e_shoff;                  // Section header offset
    Elf64_Word e_flags;                 // Processor-specific flags
    Elf64_Half e_ehsize;                // ELF header size */
    Elf64_Half e_phentsize;             // Size of program header entry
    Elf64_Half e_phnum;                 // Number of program header entries
    Elf64_Half e_shentsize;             // Size of section header entry
    Elf64_Half e_shnum;                 // Number of section header entries
    Elf64_Half e_shstrndx;              // Section name string table index
} Elf64_Ehdr;

void parse_elf64_header(Elf64_Ehdr *ehdr, FILE *file);

void print_elf64_header(Elf64_Ehdr *header);

#endif //ELF_ELF64_H
