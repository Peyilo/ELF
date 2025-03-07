#include <stdio.h>
#include <stdlib.h>
#include "elf/elf.h"

int main() {
    char *elf_list[5] = {
            "D:\\Code\\Clion\\ELF\\input\\libsfdata.so",
            "D:\\Code\\Clion\\ELF\\input\\libDexHelper.so",
            "D:\\Code\\Clion\\ELF\\input\\libDexHelper-x86.so",
            "D:\\Code\\Clion\\ELF\\input\\memdumper32",
            "D:\\Code\\Clion\\ELF\\input\\memdumper64"
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
    }
    fclose(file);
    return EXIT_SUCCESS;
}
