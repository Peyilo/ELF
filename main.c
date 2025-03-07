#include <stdio.h>
#include <stdlib.h>
#include "elf/elf.h"

#define DEVICE 2
#if DEVICE == 1
    #define SO_FILE(x) "D:\\Code\\Clion\\ELF\\input\\" x
#elif DEVICE == 2
    #define SO_FILE(x) "F:\\Code\\Clion\\ELF\\input\\" x
#endif

int main() {
    char *elf_list[5] = {
            SO_FILE("libsfdata.so"),
            SO_FILE("libDexHelper.so"),
            SO_FILE("libDexHelper-x86.so"),
            SO_FILE("memdumper32"),
            SO_FILE("memdumper64")
    };
    const char *file_path = elf_list[3];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }
    if (is_64bits(file)) {
        Elf64_Ehdr ehdr;
        parse_elf64_header(&ehdr, file);
        print_elf64_header(&ehdr);
    } else {
        Elf32_Ehdr ehdr;
        parse_elf32_header(&ehdr, file);
        print_elf32_header(&ehdr);

        Elf32_Shdr shdrs[ehdr.e_shnum];
        parse_elf32_section_header(&ehdr, shdrs, file);
        print_elf32_section_headers(&ehdr, shdrs, file);

        Elf32_Phdr phdrs[ehdr.e_phnum];
        parse_elf32_program_header(&ehdr, phdrs, file);
        print_elf32_program_headers(&ehdr, phdrs, file);
        print_elf32_seg2sec_mapping(&ehdr, phdrs, shdrs, file);

        Elf32_Phdr *dyn_phdr = get_dynamic_phdr(&ehdr, phdrs);
        int dyn_num = (int) (dyn_phdr->p_filesz / sizeof(Elf32_Dyn));
        Elf32_Dyn dyns[dyn_num];
        parse_elf32_dynamic(dyn_phdr, dyns, file);
        print_elf32_dynamic_segment(dyn_phdr, dyns, file);

        print_elf32_all_rel_section(&ehdr, shdrs, file);
        print_elf32_all_symbol_table(&ehdr, shdrs, file);
    }
    fclose(file);
    return EXIT_SUCCESS;
}
