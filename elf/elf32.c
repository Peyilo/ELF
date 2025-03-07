//
// Created by Peyilo on 2025/3/3.
//

#include "elf32.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_elf32_header(Elf32_Ehdr *ehdr, FILE *file) {
    fseek(file, 0, SEEK_SET);
    if (fread(ehdr, sizeof(Elf32_Ehdr), 1, file) != 1) {
        perror("Failed to read ELF header");
        exit(-1);
    }
}


void parse_elf32_section_header(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], FILE *file) {
    fseek(file, ehdr->e_shoff, SEEK_SET);
    if (fread(shdrs, sizeof(Elf32_Shdr), ehdr->e_shnum, file) != ehdr->e_shnum) {
        perror("Failed to read Section header");
        exit(-1);
    }
}

void parse_elf32_program_header(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], FILE *file) {
    fseek(file, ehdr->e_phoff, SEEK_SET);
    if (fread(phdrs, sizeof(Elf32_Phdr), ehdr->e_phnum, file) != ehdr->e_phnum) {
        perror("Failed to read Program header");
        exit(-1);
    }
}

// 解析 section flags 并格式化成字符串
void parse_section_flags(Elf32_Word flags, char *flag_str) {
    int pos = 0;
    if (flags & SHF_WRITE)              flag_str[pos++] = 'W';
    if (flags & SHF_ALLOC)              flag_str[pos++] = 'A';
    if (flags & SHF_EXECINSTR)          flag_str[pos++] = 'X';
    if (flags & SHF_MERGE)              flag_str[pos++] = 'M';
    if (flags & SHF_STRINGS)            flag_str[pos++] = 'S';
    if (flags & SHF_INFO_LINK)          flag_str[pos++] = 'I';
    if (flags & SHF_LINK_ORDER)         flag_str[pos++] = 'L';
    if (flags & SHF_OS_NONCONFORMING)   flag_str[pos++] = 'O';
    if (flags & SHF_GROUP)              flag_str[pos++] = 'G';
    if (flags & SHF_TLS)                flag_str[pos++] = 'T';
    if (flags & SHF_COMPRESSED)         flag_str[pos++] = 'C';
    flag_str[pos] = '\0'; // 结束符
}

// 解析 section 类型
const char *get_section_type(Elf32_Word type) {
    switch (type) {
        case SHT_NULL:              return "NULL";
        case SHT_PROGBITS:          return "PROGBITS";
        case SHT_SYMTAB:            return "SYMTAB";
        case SHT_STRTAB:            return "STRTAB";
        case SHT_RELA:              return "RELA";
        case SHT_HASH:              return "HASH";
        case SHT_DYNAMIC:           return "DYNAMIC";
        case SHT_NOTE:              return "NOTE";
        case SHT_NOBITS:            return "NOBITS";
        case SHT_REL:               return "REL";
        case SHT_SHLIB:             return "SHLIB";
        case SHT_DYNSYM:            return "DYNSYM";
        case SHT_INIT_ARRAY:        return "INIT_ARRAY";
        case SHT_FINI_ARRAY:        return "FINI_ARRAY";
        case SHT_PREINIT_ARRAY:     return "PREINIT_ARRAY";
        case SHT_GROUP:             return "GROUP";
        case SHT_NUM:               return "NUM";
        case SHT_SYMTAB_SHNDX:      return "SYMTAB_SHNDX";
        case SHT_ARM_EXIDX:         return "ARM_EXIDX";
        case SHT_VERSYM:            return "VERSYM";
        case SHT_VERNEED:           return "VERNEED";
        case SHT_GNU_HASH:          return "GNU_HASH";
        case SHT_ARM_ATTRIBUTES:    return "ARM_ATTRIBUTES";
        default:                    return "UNKNOWN";
    }
}

void print_elf32_header(Elf32_Ehdr *header) {
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
        case ET_EXEC:   printf("EXEC (Executable file)\n"); break;
        case ET_DYN:    printf("DYN (Shared object file)\n"); break;
        case ET_REL:    printf("REL (Relocatable file)\n"); break;
        default:        printf("Unknown\n"); break;
    }

    // Print machine type
    printf("  Machine:                           ");
    switch (header->e_machine) {
        case EM_386:            printf("Intel 80386\n"); break;
        case EM_X86_64:         printf("Advanced Micro Devices X86-64\n"); break;
        case EM_ARM:            printf("ARM\n"); break;
        case EM_AARCH64:        printf("AArch64\n"); break;
        default:                printf("Unknown\n"); break;
    }

    // Print other information
    printf("  Version:                           0x%X\n", header->e_version);
    printf("  Entry point address:               0x%X\n", header->e_entry);
    printf("  Start of program headers:          %u (bytes into file)\n", header->e_phoff);
    printf("  Start of section headers:          %u (bytes into file)\n", header->e_shoff);
    printf("  Flags:                             0x%X\n", header->e_flags);
    printf("  Size of this header:               %u (bytes)\n", header->e_ehsize);
    printf("  Size of program headers:           %u (bytes)\n", header->e_phentsize);
    printf("  Number of program headers:         %u\n", header->e_phnum);
    printf("  Size of section headers:           %u (bytes)\n", header->e_shentsize);
    printf("  Number of section headers:         %u\n", header->e_shnum);
    printf("  Section header string table index: %u\n\n", header->e_shstrndx);
}

// 打印sh_type为SHT_GROUP的Section信息
void print_elf32_section_group(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[]) {
    int counter = 0;
    for (int i = 0; i < ehdr->e_shnum; i++) {
        Elf32_Shdr *shdr = &shdrs[i];
        if (shdr->sh_type == SHT_GROUP) {
            counter++;
            // TODO: 打印Section group的信息
        }
    }
    if (counter == 0) {
        printf("There are no section groups in this file.\n\n");
    }
}

void read_shstrtab(Elf32_Shdr *shstrtab, char *shstrtab_data, FILE *file) {
    fseek(file, shstrtab->sh_offset, SEEK_SET);
    if (fread(shstrtab_data, 1, shstrtab->sh_size, file) != shstrtab->sh_size) {
        perror("Failed to read shstrtab");
        exit(-1);
    }
}

// 打印 ELF 节头信息
void print_elf32_section_headers(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], FILE *file) {
    Elf32_Shdr *shstrtab = &shdrs[ehdr->e_shstrndx];
    // 读取 `.shstrtab` 数据
    char shstrtab_data[shstrtab->sh_size / sizeof(char)];
    read_shstrtab(shstrtab, shstrtab_data, file);
    printf("Section Headers:\n");
    printf("  [Nr] Name                 Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
    for (int i = 0; i < ehdr->e_shnum; i++) {
        Elf32_Shdr *shdr = &shdrs[i];
        char *name = &shstrtab_data[shdr->sh_name];
        char flag_str[13] = {0};
        parse_section_flags(shdr->sh_flags, flag_str);
        printf("  [%2d] %-20s %-15s %08x %06x %06x %02x %-3s %2d %3d %2d\n",
               i, name, get_section_type(shdr->sh_type), shdr->sh_addr,
               shdr->sh_offset, shdr->sh_size, shdr->sh_entsize,
               flag_str, shdr->sh_link, shdr->sh_info, shdr->sh_addralign);
    }
    printf("Key to Flags:\n");
    printf("  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
    printf("  L (link order), O (extra OS processing required), G (group), T (TLS),\n");
    printf("  D (mbind), y (purecode), p (processor specific)\n\n");
    print_elf32_section_group(ehdr, shdrs);
}

const char* get_segment_type(uint32_t type) {
    switch (type) {
        case PT_NULL:           return "NULL";
        case PT_LOAD:           return "LOAD";
        case PT_DYNAMIC:        return "DYNAMIC";
        case PT_INTERP:         return "INTERP";
        case PT_NOTE:           return "NOTE";
        case PT_SHLIB:          return "SHLIB";
        case PT_PHDR:           return "PHDR";
        case PT_TLS:            return "TLS";
        case PT_GNU_STACK:      return "GNU_STACK";
        case PT_GNU_RELRO:      return "GNU_RELRO";
        case PT_GNU_EH_FRAME:   return "GNU_EH_FRAME";
        case PT_GNU_PROPERTY:   return "GNU_PROPERTY";
        case PT_ARM_EXIDX:      return "EXIDX";
        default:                return "UNKNOWN";
    }
}

void parse_program_flags(Elf32_Word flags, char *flag_str) {
    flag_str[0] = (flags & PF_R) ? 'R' : ' ';
    flag_str[1] = (flags & PF_W) ? 'W' : ' ';
    flag_str[2] = (flags & PF_X) ? 'E' : ' ';
    flag_str[3] = '\0';
}

void print_elf32_seg2sec_mapping(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], Elf32_Shdr shdrs[], FILE *file) {
    printf(" Section to Segment mapping:\n");
    printf("  Segment Sections...\n");
    Elf32_Shdr *shstrtab = &shdrs[ehdr->e_shstrndx];
    char shstrtab_data[shstrtab->sh_size / sizeof(char)];
    read_shstrtab(shstrtab, shstrtab_data, file);
    Elf32_Phdr *segment = NULL;
    Elf32_Shdr *section = NULL;
    for (int i = 0; i < ehdr->e_phnum; i++) {
        printf("   %02d     ", i);
        segment = phdrs + i;
        section = shdrs + 1;
        for (int j = 1; j < ehdr->e_shnum; j++, section++) {
            if (!ELF_TBSS_SPECIAL(section, segment) && ELF_SECTION_IN_SEGMENT_STRICT(section, segment)) {
                printf("%s ", &shstrtab_data[section->sh_name]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_elf32_program_headers(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], FILE *file) {
    printf("Program Headers:\n");
    printf("  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align\n");
    for (int i = 0; i < ehdr->e_phnum; i++) {
        Elf32_Phdr *phdr = phdrs + i;

        char flag_str[4] = {0};
        parse_program_flags(phdr->p_flags, flag_str);

        printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %-3s",
               get_segment_type(phdr->p_type), phdr->p_offset,
               phdr->p_vaddr, phdr->p_paddr, phdr->p_filesz, phdr->p_memsz, flag_str);

        printf(" 0x%x\n", phdr->p_align);

        // 如果是 INTERP 段，读取解释器路径
        if (phdr->p_type == PT_INTERP) {
            char interp[256] = {0};
            fseek(file, phdr->p_offset, SEEK_SET);
            fread(interp, sizeof(char), phdr->p_filesz, file);
            printf("      [Requesting program interpreter: %s]\n", interp);
        }
    }
    printf("\n");
}


Elf32_Phdr *find_phdr_by_type(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[], Elf32_Word p_type) {
    for (int i = 0; i < ehdr->e_phnum; i++) {
        Elf32_Phdr *phdr = phdrs + i;
        if (phdr->p_type == p_type) {
            return phdr;
        }
    }
    return NULL;
}

Elf32_Phdr *get_dynamic_phdr(Elf32_Ehdr *ehdr, Elf32_Phdr phdrs[]) {
    Elf32_Phdr *phdr = find_phdr_by_type(ehdr, phdrs, PT_DYNAMIC);
    if (phdr == NULL) {
        perror("Did't find the DYNAMIC segment.");
        exit(-1);
    }
    return phdr;
}


Elf32_Shdr *find_shdr_by_name(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], const char *name, FILE *file) {
    Elf32_Shdr *shstrtab = &shdrs[ehdr->e_shstrndx];
    // 读取 `.shstrtab` 数据
    char shstrtab_data[shstrtab->sh_size / sizeof(char)];
    read_shstrtab(shstrtab, shstrtab_data, file);
    for (int i = 0; i < ehdr->e_shnum; i++) {
        char *shdr_name = &shstrtab_data[(shdrs + i)->sh_name];
        if (strcmp(shdr_name, name) == 0) {
            return shdrs + i;
        }
    }
    return NULL;
}


void parse_elf32_dynamic(Elf32_Phdr *dyn_phdr, Elf32_Dyn dyns[], FILE *file) {
    fseek(file, (long) dyn_phdr->p_offset, SEEK_SET);
    if (fread(dyns, dyn_phdr->p_filesz, 1, file) != 1) {
        perror("Failed to read Dynamic Segment");
        exit(-1);
    }
}


void get_elf32_dynamic_flag(Elf32_Word flag, char *res) {
    res[0] = '\0'; // 清空结果字符串
    int first = 1;
    // DT_FLAGS
    if (flag & DF_ORIGIN) {
        strcat(res, "ORIGIN");
        first = 0;
    }
    if (flag & DF_SYMBOLIC) {
        strcat(res, first ? "SYMBOLIC" : " SYMBOLIC");
        first = 0;
    }
    if (flag & DF_TEXTREL) {
        strcat(res, first ? "TEXTREL" : " TEXTREL");
        first = 0;
    }
    if (flag & DF_BIND_NOW) {
        strcat(res, first ? "BIND_NOW" : " BIND_NOW");
        first = 0;
    }
    if (flag & DF_STATIC_TLS) {
        strcat(res, first ? "STATIC_TLS" : " STATIC_TLS");
        first = 0;
    }
    if (first) { // 如果没有任何 flag 设置
        strcat(res, "NONE");
    }
}

void get_elf32_dynamic_flag1(Elf32_Word flag, char *res) {
    res[0] = '\0'; // 清空结果字符串
    int first = 1;

    // DT_FLAGS_1
    if (flag & DF_1_NOW) {
        strcat(res, "NOW");
        first = 0;
    }
    if (flag & DF_1_GLOBAL) {
        strcat(res, first ? "GLOBAL" : " GLOBAL");
        first = 0;
    }
    if (flag & DF_1_GROUP) {
        strcat(res, first ? "GROUP" : " GROUP");
        first = 0;
    }
    if (flag & DF_1_NODELETE) {
        strcat(res, first ? "NODELETE" : " NODELETE");
        first = 0;
    }
    if (flag & DF_1_LOADFLTR) {
        strcat(res, first ? "LOADFLTR" : " LOADFLTR");
        first = 0;
    }
    if (flag & DF_1_INITFIRST) {
        strcat(res, first ? "INITFIRST" : " INITFIRST");
        first = 0;
    }
    if (flag & DF_1_NOOPEN) {
        strcat(res, first ? "NOOPEN" : " NOOPEN");
        first = 0;
    }
    if (flag & DF_1_ORIGIN) {
        strcat(res, first ? "ORIGIN" : " ORIGIN");
        first = 0;
    }
    if (flag & DF_1_DIRECT) {
        strcat(res, first ? "DIRECT" : " DIRECT");
        first = 0;
    }
    if (flag & DF_1_TRANS) {
        strcat(res, first ? "TRANS" : " TRANS");
        first = 0;
    }
    if (flag & DF_1_INTERPOSE) {
        strcat(res, first ? "INTERPOSE" : " INTERPOSE");
        first = 0;
    }
    if (flag & DF_1_NODEFLIB) {
        strcat(res, first ? "NODEFLIB" : " NODEFLIB");
        first = 0;
    }
    if (flag & DF_1_NODUMP) {
        strcat(res, first ? "NODUMP" : " NODUMP");
        first = 0;
    }
    if (flag & DF_1_CONFALT) {
        strcat(res, first ? "CONFALT" : " CONFALT");
        first = 0;
    }
    if (flag & DF_1_ENDFILTEE) {
        strcat(res, first ? "ENDFILTEE" : " ENDFILTEE");
        first = 0;
    }
    if (flag & DF_1_DISPRELDNE) {
        strcat(res, first ? "DISPRELDNE" : " DISPRELDNE");
        first = 0;
    }
    if (flag & DF_1_DISPRELPND) {
        strcat(res, first ? "DISPRELPND" : " DISPRELPND");
        first = 0;
    }
    if (flag & DF_1_NODIRECT) {
        strcat(res, first ? "NODIRECT" : " NODIRECT");
        first = 0;
    }
    if (flag & DF_1_IGNMULDEF) {
        strcat(res, first ? "IGNMULDEF" : " IGNMULDEF");
        first = 0;
    }
    if (flag & DF_1_NOKSYMS) {
        strcat(res, first ? "NOKSYMS" : " NOKSYMS");
        first = 0;
    }
    if (flag & DF_1_NOHDR) {
        strcat(res, first ? "NOHDR" : " NOHDR");
        first = 0;
    }
    if (flag & DF_1_EDITED) {
        strcat(res, first ? "EDITED" : " EDITED");
        first = 0;
    }
    if (flag & DF_1_NORELOC) {
        strcat(res, first ? "NORELOC" : " NORELOC");
        first = 0;
    }
    if (flag & DF_1_SYMINTPOSE) {
        strcat(res, first ? "SYMINTPOSE" : " SYMINTPOSE");
        first = 0;
    }
    if (flag & DF_1_GLOBAUDIT) {
        strcat(res, first ? "GLOBAUDIT" : " GLOBAUDIT");
        first = 0;
    }
    if (flag & DF_1_SINGLETON) {
        strcat(res, first ? "SINGLETON" : " SINGLETON");
        first = 0;
    }
    if (flag & DF_1_PIE) {
        strcat(res, first ? "PIE" : " PIE");
        first = 0;
    }

    if (first) { // 如果没有任何 flag 设置
        strcat(res, "NONE");
    }
}

void print_elf32_dynamic_segment(Elf32_Phdr *dyn_phdr, Elf32_Dyn dyns[], FILE *file) {
    // **3. 遍历 Dynamic Section，解析重要的 Tag**
    printf("Dynamic section at offset 0x%x contains %d entries:\n", dyn_phdr->p_offset, (int)(dyn_phdr->p_filesz / sizeof(Elf32_Dyn)));
    printf("  Tag        Type                         Name/Value\n");
    Elf32_Word strsz = 0;
    Elf32_Addr strtab;
    for (Elf32_Dyn *dyn = dyns; dyn->d_tag != DT_NULL; dyn++) {
        if (dyn->d_tag == DT_STRTAB) {
            strtab = dyn->d_un.d_ptr;
        }
        if (dyn->d_tag == DT_STRSZ) {
            strsz = dyn->d_un.d_val;
        }
    }
    char dynamic_str[strsz / sizeof(char)];
    if (strsz != 0) {
        fseek(file, strtab, SEEK_SET);
        if (fread(dynamic_str, strsz, 1, file) != 1) {
            perror("Failed to read Dynamic STRTAB");
            exit(-1);
        }
    }
    for (int i = 0; i < dyn_phdr->p_filesz / sizeof(Elf32_Dyn); i++) {
        Elf32_Dyn *dyn = dyns + i;
        printf(" 0x%08x ", dyn->d_tag);
        switch (dyn->d_tag) {
            case DT_NULL:
                printf("(NULL)                       0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_NEEDED:
                printf("(NEEDED)                     Shared library: [%s]\n", dynamic_str + dyn->d_un.d_val);
                break;
            case DT_PLTRELSZ:
                printf("(PLTRELSZ)                   %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_PLTGOT:
                printf("(PLTGOT)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_PLTREL: {
                printf("(PLTREL)                     %s\n", dyn->d_un.d_val == DT_REL ? "REL" : "RELA");
                break;
            }
            case DT_HASH:
                printf("(HASH)                       0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_STRTAB:
                printf("(STRTAB)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_SYMTAB:
                printf("(SYMTAB)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_STRSZ:
                printf("(STRSZ)                      %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_SYMENT:
                printf("(SYMENT)                     %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_INIT:
                printf("(INIT)                       0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_SONAME:
                printf("(SONAME)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_FINI:
                printf("(FINI)                       0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_RELA:
                printf("(RELA)                       0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_RELASZ:
                printf("(RELASZ)                     %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_RELAENT:
                printf("(RELAENT)                    %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_REL:
                printf("(REL)                        0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_RELSZ:
                printf("(RELSZ)                      %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_RELENT:
                printf("(RELENT)                     %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_RELCOUNT:
                printf("(RELCOUNT)                   %u\n", dyn->d_un.d_val);
                break;
            case DT_JMPREL:
                printf("(JMPREL)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_DEBUG:
                printf("(DEBUG)                      0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_FLAGS: {
                char res[100];
                get_elf32_dynamic_flag(dyn->d_un.d_val, res);
                printf("(FLAGS)                      %s\n", res);
                break;
            }
            case DT_FLAGS_1: {
                char res[100];
                get_elf32_dynamic_flag1(dyn->d_un.d_val, res);
                printf("(FLAGS_1)                    Flags: %s\n", res);
                break;
            }
            case DT_INIT_ARRAY:
                printf("(INIT_ARRAY)                 0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_INIT_ARRAYSZ:
                printf("(INIT_ARRAYSZ)               %u (bytes)\n", dyn->d_un.d_val);
                break;
            case DT_VERSYM:
                printf("(VERSYM)                     0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_VERNEED:
                printf("(VERNEED)                    0x%x\n", dyn->d_un.d_ptr);
                break;
            case DT_VERNEEDNUM:
                printf("(VERNEEDNUM)                 %u\n", dyn->d_un.d_val);
                break;
            case DT_GNU_HASH:
                printf("(GNU_HASH)                   0x%x\n", dyn->d_un.d_ptr);
                break;
            default:
                printf("(UNKNOWN)                    0x%x\n", dyn->d_un.d_val);
                break;
        }
    }
    printf("\n");
}


void parse_elf32_rel(Elf32_Shdr *rel_shdr, Elf32_Rel rels[], FILE *file) {
    if (rel_shdr->sh_type != SHT_REL) {
        perror("The type of the rel_shdr must to be SHT_REL!");
        exit(-1);
    }
    fseek(file, (long )rel_shdr->sh_offset, SEEK_SET);
    if (fread(rels, rel_shdr->sh_size, 1, file) != 1) {
        perror("Failed to read rel section");
        exit(-1);
    }
}

// 打印符号表信息（符号索引与符号名称）
void print_symbol_info(Elf32_Sym *symtab, unsigned int symbol_index, FILE *file) {
    // 假设你有符号表的指针 `symtab` 和 ELF 文件 `file`
    if (!symtab) return;

    // 获取符号名称，假设符号名在符号字符串表中
    fseek(file, symtab[symbol_index].st_name, SEEK_SET);
    char symbol_name[256];
    fread(symbol_name, sizeof(char), sizeof(symbol_name) - 1, file);
    symbol_name[255] = '\0'; // 确保符号名称是字符串

    printf("  Symbol Index: %u\n", symbol_index);
    printf("  Symbol Name: %s\n", symbol_name);
}

char *get_relocation_type(unsigned int relocation_type) {
    switch (relocation_type) {
        case R_ARM_NONE:              return "ARM_NONE";
        case R_ARM_PC24:              return "R_ARM_PC24";
        case R_ARM_ABS32:             return "R_ARM_ABS32";
        case R_ARM_REL32:             return "R_ARM_REL32";
        case R_ARM_LDR_PC_G0:         return "R_ARM_LDR_PC_G0";
        case R_ARM_ABS16:             return "R_ARM_ABS16";
        case R_ARM_ABS12:             return "R_ARM_ABS12";
        case R_ARM_THM_ABS5:          return "R_ARM_THM_ABS5";
        case R_ARM_ABS8:              return "R_ARM_ABS8";
        case R_ARM_SBREL32:           return "R_ARM_SBREL32";
        case R_ARM_THM_CALL:          return "R_ARM_THM_CALL";
        case R_ARM_THM_PC8:           return "R_ARM_THM_PC8";
        case R_ARM_BREL_ADJ:          return "R_ARM_BREL_ADJ";
        case R_ARM_TLS_DESC:          return "R_ARM_TLS_DESC";
        case R_ARM_THM_SWI8:          return "R_ARM_THM_SWI8";
        case R_ARM_XPC25:             return "R_ARM_XPC25";
        case R_ARM_THM_XPC22:         return "R_ARM_THM_XPC22";
        case R_ARM_TLS_DTPMOD32:      return "R_ARM_TLS_DTPMOD32";
        case R_ARM_TLS_DTPOFF32:      return "R_ARM_TLS_DTPOFF32";
        case R_ARM_TLS_TPOFF32:       return "R_ARM_TLS_TPOFF32";
        case R_ARM_COPY:              return "R_ARM_COPY";
        case R_ARM_GLOB_DAT:          return "R_ARM_GLOB_DAT";
        case R_ARM_JUMP_SLOT:         return "R_ARM_JUMP_SLOT";
        case R_ARM_RELATIVE:          return "R_ARM_RELATIVE";
        case R_ARM_GOTOFF32:          return "R_ARM_GOTOFF32";
        case R_ARM_BASE_PREL:         return "R_ARM_BASE_PREL";
        case R_ARM_GOT_BREL:          return "R_ARM_GOT_BREL";
        case R_ARM_PLT32:             return "R_ARM_PLT32";
        case R_ARM_CALL:              return "R_ARM_CALL";
        case R_ARM_JUMP24:            return "R_ARM_JUMP24";
        case R_ARM_THM_JUMP24:        return "R_ARM_THM_JUMP24";
        case R_ARM_BASE_ABS:          return "R_ARM_BASE_ABS";
        case R_ARM_ALU_PCREL_7_0:     return "R_ARM_ALU_PCREL_7_0";
        case R_ARM_ALU_PCREL_15_8:    return "R_ARM_ALU_PCREL_15_8";
        case R_ARM_ALU_PCREL_23_15:   return "R_ARM_ALU_PCREL_23_15";
        case R_ARM_LDR_SBREL_11_0_NC: return "R_ARM_LDR_SBREL_11_0_NC";
        case R_ARM_ALU_SBREL_19_12_NC: return "R_ARM_ALU_SBREL_19_12_NC";
        case R_ARM_ALU_SBREL_27_20_CK: return "R_ARM_ALU_SBREL_27_20_CK";
        case R_ARM_TARGET1:           return "R_ARM_TARGET1";

        default:                      return "Unknown";
    }
}


void print_elf32_reldyn_section(Elf32_Ehdr *ehdr, Elf32_Shdr shdrs[], Elf32_Shdr *rel_shdr, Elf32_Rel rels[], FILE *file) {
    size_t size = rel_shdr->sh_size / sizeof(Elf32_Rel);
    printf("Relocation section '.rel.dyn' at offset 0x%x contains %zu entries:\n", rel_shdr->sh_offset, size);
    printf(" Offset     Info    Type            Sym.Value  Sym. Name\n");

    // TODO: Sym信息有问题
    Elf32_Shdr *dynstr_shdr = find_shdr_by_name(ehdr, shdrs, ".dynstr", file);
    char strtab[dynstr_shdr->sh_size / sizeof(char )];
    fseek(file, (long )dynstr_shdr->sh_offset, SEEK_SET);
    if (fread(strtab, dynstr_shdr->sh_size, 1, file) != 1) {
        perror("Failed to read .dynstr section");
        exit(-1);
    }

    // 遍历每个重定位条目
    for (size_t i = 0; i < size; ++i) {
        Elf32_Rel *rel_entry = &rels[i];

        // 获取符号索引和重定位类型
        unsigned int symbol_index = ELF32_R_SYM(rel_entry->r_info);
        unsigned int relocation_type = ELF32_R_TYPE(rel_entry->r_info);

        printf("%08x  %08x %s %s\n", rel_entry->r_offset, rel_entry->r_info, get_relocation_type(relocation_type), strtab + symbol_index);

    }
}