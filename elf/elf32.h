//
// Created by Peyilo on 2025/3/3.
//

#ifndef ELF_ELF32_H
#define ELF_ELF32_H

#include <stdint.h>
#include <stdio.h>
#include "internal.h"

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;

// define the ELF Header
typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;                     // Entry point address
    Elf32_Off e_phoff;                      // Start of program headers
    Elf32_Off e_shoff;                      // Start of section headers
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;                    // Size of ELF header
    Elf32_Half e_phentsize;                 // Size of program headers
    Elf32_Half e_phnum;                     // Number of program headers
    Elf32_Half e_shentsize;                 // Size of section headers
    Elf32_Half e_shnum;                     // Number of section headers
    Elf32_Half e_shstrndx;                  // Section header string table index
} Elf32_Ehdr;

// define the section header
typedef struct {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Word sh_addr;
    Elf32_Word sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

// define the program header
typedef struct {
    Elf32_Word p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz;
    Elf32_Word p_memsz;
    Elf32_Word p_flags;
    Elf32_Word p_align;
} Elf32_Phdr;

// define the Dynamic section entry
typedef struct {
    Elf32_Sword d_tag;
    union {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;

// define the Symbol table entry
typedef struct {
    Elf32_Word      st_name;
    Elf32_Addr      st_value;
    Elf32_Word      st_size;
    unsigned char   st_info;
    unsigned char   st_other;
    Elf32_Half      st_shndx;
} Elf32_Sym;

// Define the relocation entry
typedef struct {
    Elf32_Addr      r_offset;
    Elf32_Word      r_info;
} Elf32_Rel;

typedef struct {
    Elf32_Addr      r_offset;
    Elf32_Word      r_info;
    Elf32_Sword     r_addend;
} Elf32_Rela;


void parse_elf32_header(Elf32_Ehdr *ehdr, FILE *file);
void parse_elf32_section_header(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], FILE *file);
void parse_elf32_program_header(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], FILE *file);
void parse_elf32_dynamic(Elf32_Phdr *dyn_phdr, Elf32_Dyn dyns[], FILE *file);
void parse_elf32_rel(Elf32_Shdr *rel_shdr, Elf32_Rel rels[], FILE *file);

void print_elf32_header(Elf32_Ehdr *header);
void print_elf32_section_headers(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], FILE *file);
void print_elf32_program_headers(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], FILE *file);
void print_elf32_seg2sec_mapping(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], Elf32_Shdr shdrs[], FILE *file);
void print_elf32_dynamic_segment(Elf32_Phdr *dyn_phdr, Elf32_Dyn dyns[], FILE *file);
void print_elf32_reldyn_section(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], Elf32_Shdr *rel_shdr, Elf32_Rel rels[], FILE *file);

Elf32_Shdr *find_shdr_by_name(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], const char *name, FILE *file);
Elf32_Phdr *find_phdr_by_type(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], Elf32_Word p_type);

Elf32_Phdr *get_dynamic_phdr(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[]);


#endif //ELF_ELF32_H
