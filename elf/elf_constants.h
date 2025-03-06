//
// Created by Peyilo on 2025/3/3.
//

#ifndef ELF_ELF_CONSTANTS_H
#define ELF_ELF_CONSTANTS_H

// e_ident索引
#define EI_MAG0         0
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_OSABI        7
#define EI_ABIVERSION   8
#define EI_PAD          9
#define EI_NIDENT       16

// e_ident[EI_CLASS]取值
#define ELFCLASSNONE    0
#define ELFCLASS32      1       // 32-bit objects
#define ELFCLASS64      2       // 64-bit objects

// e_ident[EI_DATA]取值
#define ELFDATANONE     0
#define ELFDATA2LSB     1       // little endian
#define ELFDATA2MSB     2       // big endian

// e_ident[EI_OSABI]的取值
#define ELFOSABI_SYSV   0
#define ELFOSABI_LINUX  3

// e_type: This member identifies the object file type
#define ET_NONE     0           // No file type
#define ET_REL      1           // Relocatable file
#define ET_EXEC     2           // Executable file
#define ET_DYN      3           // Shared object file
#define ET_CORE     4           // Core file
#define ET_LOPROC   0xff00      // Processor-specific
#define ET_HIPROC   0xffff      // Processor-specific

// e_machine的取值
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3       // Intel 80386
#define EM_68K          4
#define EM_88K          5
#define EM_860          7
#define EM_MIPS         8
#define EM_MIPS_RS4_BE  10
#define EM_ARM          0x28    // 40: Arm (up to Armv7/AArch32)
#define EM_X86_64       0x3E    // 62: AMD x86-64
#define EM_AARCH64      0xB7    // 183: Arm 64-bits (Armv8/AArch64)


// Section type: sh_type
#define SHT_NULL            0
#define SHT_PROGBITS        1
#define SHT_SYMTAB          2
#define SHT_STRTAB          3
#define SHT_RELA            4
#define SHT_HASH            5
#define SHT_DYNAMIC         6
#define SHT_NOTE            7
#define SHT_NOBITS          8
#define SHT_REL             9
#define SHT_SHLIB           10
#define SHT_DYNSYM          11
#define SHT_INIT_ARRAY      14
#define SHT_FINI_ARRAY      15
#define SHT_PREINIT_ARRAY   16
#define SHT_GROUP           17
#define SHT_SYMTAB_SHNDX    18
#define SHT_NUM             19
#define SHT_ARM_EXIDX       0x70000001
#define SHT_VERSYM          0x6fffffff
#define SHT_VERNEED         0x6ffffffe
#define SHT_GNU_HASH        0x6ffffff6
#define SHT_ARM_ATTRIBUTES  0x70000003
#define SHT_LOOS            0x60000000
#define SHT_HIOS            0x6fffffff
#define SHT_LOPROC          0x70000000
#define SHT_HITPROC         0x7fffffff
#define SHT_LOUSER          0x80000000
#define SHT_HIUSER          0xffffffff

// Section flags: sh_flags
#define SHF_WRITE               (1 << 0)   /* Writable */
#define SHF_ALLOC               (1 << 1)   /* Occupies memory during execution */
#define SHF_EXECINSTR           (1 << 2)   /* Executable */
#define SHF_MERGE               (1 << 4)   /* Might be merged */
#define SHF_STRINGS             (1 << 5)   /* Contains nul-terminated strings */
#define SHF_INFO_LINK           (1 << 6)   /* `sh_info' contains SHT index */
#define SHF_LINK_ORDER          (1 << 7)   /* Preserve order after combining */
#define SHF_OS_NONCONFORMING    (1 << 8)   /* Non-standard OS specific handling required */
#define SHF_GROUP               (1 << 9)   /* Section is member of a group.  */
#define SHF_TLS                 (1 << 10)  /* Section hold thread-local data.  */
#define SHF_COMPRESSED          (1 << 11)
#define SHF_MASKOS              0x0ff00000 /* OS-specific.  */
#define SHF_MASKPROC            0xf0000000 /* Processor-specific */
#define SHF_ORDERED             (1 << 30)  /* Special ordering requirement (Solaris).  */
#define SHF_EXCLUDE             (1 << 31)  /* Section is excluded unless referenced or allocated (Solaris).*/


// Segment type: p_type
#define PT_NULL                 0
#define PT_LOAD                 1
#define PT_DYNAMIC              2
#define PT_INTERP               3
#define PT_NOTE                 4
#define PT_SHLIB                5
#define PT_PHDR                 6
#define PT_TLS                  7
#define PT_NUM                  8
#define PT_LOOS                 0x60000000  /* OS-specific */
#define PT_GNU_EH_FRAME         0x6474e550  /* GCC .eh_frame_hdr segment */
#define PT_GNU_STACK            0x6474e551  /* Indicates stack executability */
#define PT_GNU_RELRO            0x6474e552  /* Read-only after relocation */
#define PT_GNU_PROPERTY         0x6474e553  /* GNU property */
#define PT_ARM_EXIDX            0x70000001  /* Exception unwind tables */

// program flags
#define PF_X        0x1   /* Execute permission */
#define PF_W        0x2   /* Write permission */
#define PF_R        0x4   /* Read permission */
#define PF_MASKOS   0x0ff00000  /* OS-specific */
#define PF_MASKPROC 0xf0000000  /* Processor-specific */

// Dynamic segment
#define DT_NULL          0   /* 结束标记 (End of .dynamic section) */
#define DT_NEEDED        1   /* 依赖的共享库 (Name of needed library) */
#define DT_PLTRELSZ      2   /* PLT 重定位表大小 (Size in bytes of PLT relocs) */
#define DT_PLTGOT        3   /* GOT 表地址 (Processor-defined address) */
#define DT_HASH          4   /* 符号哈希表地址 (Address of symbol hash table) */
#define DT_STRTAB        5   /* 字符串表地址 (Address of string table) */
#define DT_SYMTAB        6   /* 符号表地址 (Address of symbol table) */
#define DT_RELA          7   /* RELA 重定位表地址 (Address of Rela relocation table) */
#define DT_RELASZ        8   /* RELA 表大小 (Size in bytes of Rela relocations) */
#define DT_RELAENT       9   /* RELA 表项大小 (Size of one Rela relocation entry) */
#define DT_STRSZ         10  /* 字符串表大小 (Size in bytes of string table) */
#define DT_SYMENT        11  /* 符号表项大小 (Size of one symbol table entry) */
#define DT_INIT          12  /* `.init` 段地址 (Address of initialization function) */
#define DT_FINI          13  /* `.fini` 段地址 (Address of termination function) */
#define DT_SONAME        14  /* 共享库名称 (Shared object name) */
#define DT_RPATH         15  /* 运行路径 (Library search path) [已废弃] */
#define DT_SYMBOLIC      16  /* 符号解析策略 (Start symbol search in shared object) */
#define DT_REL           17  /* REL 重定位表地址 (Address of Rel relocation table) */
#define DT_RELSZ         18  /* REL 表大小 (Size in bytes of Rel relocations) */
#define DT_RELENT        19  /* REL 表项大小 (Size of one Rel relocation entry) */
#define DT_PLTREL        20  /* PLT 重定位类型 (Type of relocations used for PLT) */
#define DT_DEBUG         21  /* 调试用途 (Debugging information) */
#define DT_TEXTREL       22  /* 允许文本重定位 (Relocations might modify .text) */
#define DT_JMPREL        23  /* PLT 重定位表地址 (Address of PLT relocations) */
#define DT_BIND_NOW      24  /* 立即绑定 (Process all relocations before execution) */
#define DT_INIT_ARRAY    25  /* 初始化数组 (Pointer to array of initialization functions) */
#define DT_FINI_ARRAY    26  /* 终止数组 (Pointer to array of termination functions) */
#define DT_INIT_ARRAYSZ  27  /* 初始化数组大小 (Size in bytes of DT_INIT_ARRAY) */
#define DT_FINI_ARRAYSZ  28  /* 终止数组大小 (Size in bytes of DT_FINI_ARRAY) */
#define DT_RUNPATH       29  /* 运行时路径 (Library search path) */
#define DT_FLAGS         30  /* 标志 (Flags for object loading) */
#define DT_ENCODING      32  /* 编码 (Values for subsequent DT_* entries) */

#define DT_PREINIT_ARRAY 32  /* 预初始化数组 (Pointer to array of pre-init functions) */
#define DT_PREINIT_ARRAYSZ 33 /* 预初始化数组大小 (Size in bytes of DT_PREINIT_ARRAY) */
#define DT_SYMTAB_SHNDX  34  /* 符号表索引 (Address of section associated with symbol table) */
#define DT_RELCOUNT      0x6ffffffa /* REL 重定位项数量 */
#define DT_FLAGS_1       0x6ffffffb /* 额外的 FLAGS_1 标志 */
#define DT_VERDEF        0x6ffffffc /* 版本定义表 */
#define DT_VERDEFNUM     0x6ffffffd /* 版本定义条目数 */
#define DT_VERNEED       0x6ffffffe /* 版本需求表 */
#define DT_VERNEEDNUM    0x6fffffff /* 版本需求条 */
#define DT_VERSYM        0x6ffffff0

#endif //ELF_ELF_CONSTANTS_H
