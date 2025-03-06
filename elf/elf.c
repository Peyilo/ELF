//
// Created by Peyilo on 2025/3/3.
//
#include "elf.h"
#include <stdlib.h>

bool check_magic(const unsigned char *e_ident) {
    // Check ELF magic number: '0x7f' 'E' 'L' 'F'
    if (e_ident[EI_MAG0] != 0x7F || e_ident[EI_MAG1] != 'E' ||
        e_ident[EI_MAG2] != 'L' || e_ident[EI_MAG3] != 'F') {
        return false;
    }
    return true;
}

bool is_64bits(FILE *file) {
    fseek(file, 0, SEEK_SET);
    unsigned char e_ident[EI_NIDENT];
    if (fread(e_ident, sizeof(e_ident), 1, file) != 1) {
        perror("Failed to read ELF header\n");
        exit(-1);
    }
    bool validate = check_magic(e_ident);
    if (!validate) {
        perror("Not a valid ELF file\n");
        exit(-1);
    }
    if (e_ident[EI_CLASS] == ELFCLASS32) {
        return false;
    } else if (e_ident[EI_CLASS] == ELFCLASS64) {
        return true;
    } else {
        perror("Unkown EI_CLASS\n");
        exit(-1);
    }
}