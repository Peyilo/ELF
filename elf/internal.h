//
// Created by Peyilo on 2025/3/3.
//

#ifndef ELF_INTERNAL_H
#define ELF_INTERNAL_H

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
#define DT_GNU_HASH      0x6ffffef5

// DT_FLAGS
#define DF_ORIGIN       0x00000001  // 允许 `$ORIGIN`
#define DF_SYMBOLIC     0x00000002  // 先查找自身的符号
#define DF_TEXTREL      0x00000004  // 允许对 `.text` 段进行写操作
#define DF_BIND_NOW     0x00000008  // 强制立即解析所有符号
#define DF_STATIC_TLS   0x00000010  // 共享库需要静态 TLS 分配

// DT_FLAGS_1
#define DF_1_NOW        0x00000001  // 立即绑定所有符号（类似 `DF_BIND_NOW`）
#define DF_1_GLOBAL     0x00000002  // 使该共享库的符号全局可见
#define DF_1_GROUP      0x00000004  // 共享库属于一个符号解析组
#define DF_1_NODELETE   0x00000008  // 共享库不会被 `dlclose()` 卸载
#define DF_1_LOADFLTR   0x00000010  // 立即加载所有 `DT_FILTER`
#define DF_1_INITFIRST  0x00000020  // 该共享库的 `init` 代码优先执行
#define DF_1_NOOPEN     0x00000040  // 不能被 `dlopen()` 动态加载
#define DF_1_ORIGIN     0x00000080  // 允许 `$ORIGIN` 变量
#define DF_1_DIRECT     0x00000100  // 直接绑定符号，避免符号查找
#define DF_1_TRANS      0x00000200  // 透明对象（通常用于 RTLD_GLOBAL）
#define DF_1_INTERPOSE  0x00000400  // 该库的符号会替换之前加载的符号
#define DF_1_NODEFLIB   0x00000800  // 禁止默认库搜索路径
#define DF_1_NODUMP     0x00001000  // 该库不会被 `ldd` 或 `gdb` dump
#define DF_1_CONFALT    0x00002000  // 允许 `DT_CONFIG` 指定备用路径
#define DF_1_ENDFILTEE  0x00004000  // 该库是 `DT_FILTER` 的终点
#define DF_1_DISPRELDNE 0x00008000  // 推迟 `DT_REL` 处理
#define DF_1_DISPRELPND 0x00010000  // 提前 `DT_REL` 处理
#define DF_1_NODIRECT   0x00020000  // 禁止 `DT_DIRECT`
#define DF_1_IGNMULDEF  0x00040000  // 忽略多次定义的符号
#define DF_1_NOKSYMS    0x00080000  // 该库没有 `.dynsym` 符号表
#define DF_1_NOHDR      0x00100000  // 禁止加载 ELF 头
#define DF_1_EDITED     0x00200000  // 该库已被修改（可能是热修复）
#define DF_1_NORELOC    0x00400000  // 禁止 `.rel` 和 `.rela` 解析
#define DF_1_SYMINTPOSE 0x00800000  // 该库的符号会插入全局符号表
#define DF_1_GLOBAUDIT  0x01000000  // 该库会影响 `audit` 机制
#define DF_1_SINGLETON  0x02000000  // 该库在整个进程中唯一
#define DF_1_PIE        0x08000000


/* Mbind segments */
#define PT_GNU_MBIND_NUM 4096
#define PT_GNU_MBIND_LO (PT_LOOS + 0x474e555)
#define PT_GNU_MBIND_HI (PT_GNU_MBIND_LO + PT_GNU_MBIND_NUM - 1)
#define PT_GNU_SFRAME	(PT_LOOS + 0x474e554) /* SFrame stack trace information */

#include <stdint.h>
typedef uint32_t bfd_vma;

/* .tbss is special.  It doesn't contribute memory space to normal
   segments and it doesn't take file space in normal segments.  */
#define ELF_TBSS_SPECIAL(sec_hdr, segment)			\
  (((sec_hdr)->sh_flags & SHF_TLS) != 0				\
   && (sec_hdr)->sh_type == SHT_NOBITS				\
   && (segment)->p_type != PT_TLS)

#define ELF_SECTION_SIZE(sec_hdr, segment)			\
  (ELF_TBSS_SPECIAL(sec_hdr, segment) ? 0 : (sec_hdr)->sh_size)

/* Decide if the section SEC_HDR is in SEGMENT.  If CHECK_VMA, then
   VMAs are checked for alloc sections.  If STRICT, then a zero size
   section won't match at the end of a segment, unless the segment
   is also zero size.  Regardless of STRICT and CHECK_VMA, zero size
   sections won't match at the start or end of PT_DYNAMIC nor PT_NOTE,
   unless PT_DYNAMIC and PT_NOTE are themselves zero sized.  */
#define ELF_SECTION_IN_SEGMENT_1(sec_hdr, segment, check_vma, strict)	\
  ((/* Only PT_LOAD, PT_GNU_RELRO and PT_TLS segments can contain	\
       SHF_TLS sections.  */						\
    ((((sec_hdr)->sh_flags & SHF_TLS) != 0)				\
     && ((segment)->p_type == PT_TLS					\
	 || (segment)->p_type == PT_GNU_RELRO				\
	 || (segment)->p_type == PT_LOAD))				\
    /* PT_TLS segment contains only SHF_TLS sections, PT_PHDR no	\
       sections at all.  */						\
    || (((sec_hdr)->sh_flags & SHF_TLS) == 0				\
	&& (segment)->p_type != PT_TLS					\
	&& (segment)->p_type != PT_PHDR))				\
   /* PT_LOAD and similar segments only have SHF_ALLOC sections.  */	\
   && !(((sec_hdr)->sh_flags & SHF_ALLOC) == 0				\
	&& ((segment)->p_type == PT_LOAD				\
	    || (segment)->p_type == PT_DYNAMIC				\
	    || (segment)->p_type == PT_GNU_EH_FRAME			\
	    || (segment)->p_type == PT_GNU_STACK			\
	    || (segment)->p_type == PT_GNU_RELRO			\
	    || (segment)->p_type == PT_GNU_SFRAME			\
	    || ((segment)->p_type >= PT_GNU_MBIND_LO			\
		&& (segment)->p_type <= PT_GNU_MBIND_HI)))		\
   /* Any section besides one of type SHT_NOBITS must have file		\
      offsets within the segment.  */					\
   && ((sec_hdr)->sh_type == SHT_NOBITS					\
       || ((bfd_vma) (sec_hdr)->sh_offset >= (segment)->p_offset	\
	   && (!(strict)						\
	       || ((sec_hdr)->sh_offset - (segment)->p_offset		\
		   <= (segment)->p_filesz - 1))				\
	   && (((sec_hdr)->sh_offset - (segment)->p_offset		\
		+ ELF_SECTION_SIZE(sec_hdr, segment))			\
	       <= (segment)->p_filesz)))				\
   /* SHF_ALLOC sections must have VMAs within the segment.  */		\
   && (!(check_vma)							\
       || ((sec_hdr)->sh_flags & SHF_ALLOC) == 0			\
       || ((sec_hdr)->sh_addr >= (segment)->p_vaddr			\
	   && (!(strict)						\
	       || ((sec_hdr)->sh_addr - (segment)->p_vaddr		\
		   <= (segment)->p_memsz - 1))				\
	   && (((sec_hdr)->sh_addr - (segment)->p_vaddr			\
		+ ELF_SECTION_SIZE(sec_hdr, segment))			\
	       <= (segment)->p_memsz)))					\
   /* No zero size sections at start or end of PT_DYNAMIC nor		\
      PT_NOTE.  */							\
   && (((segment)->p_type != PT_DYNAMIC					\
	&& (segment)->p_type != PT_NOTE)				\
       || (sec_hdr)->sh_size != 0					\
       || (segment)->p_memsz == 0					\
       || (((sec_hdr)->sh_type == SHT_NOBITS				\
	    || ((bfd_vma) (sec_hdr)->sh_offset > (segment)->p_offset	\
	        && ((sec_hdr)->sh_offset - (segment)->p_offset		\
		    < (segment)->p_filesz)))				\
	   && (((sec_hdr)->sh_flags & SHF_ALLOC) == 0			\
	       || ((sec_hdr)->sh_addr > (segment)->p_vaddr		\
		   && ((sec_hdr)->sh_addr - (segment)->p_vaddr		\
		       < (segment)->p_memsz))))))

#define ELF_SECTION_IN_SEGMENT(sec_hdr, segment)			\
  (ELF_SECTION_IN_SEGMENT_1 (sec_hdr, segment, 1, 0))

#define ELF_SECTION_IN_SEGMENT_STRICT(sec_hdr, segment)			\
  (ELF_SECTION_IN_SEGMENT_1 (sec_hdr, segment, 1, 1))

// Relocation section type
#define R_ARM_NONE              0   // Static Misc
#define R_ARM_PC24              1   // Deprecated ARM ((S + A) | T) - P
#define R_ARM_ABS32             2   // Static Data (S + A) | T
#define R_ARM_REL32             3   // Static Data ((S + A) | T) - P
#define R_ARM_LDR_PC_G0         4   // Static ARM S + A - P
#define R_ARM_ABS16             5   // Static Data S + A
#define R_ARM_ABS12             6   // Static ARM S + A
#define R_ARM_THM_ABS5          7   // Static Thumb16 S + A
#define R_ARM_ABS8              8   // Static Data S + A
#define R_ARM_SBREL32           9   // Static Data ((S + A) | T) - B(S)
#define R_ARM_THM_CALL         10   // Static Thumb32 ((S + A) | T) - P
#define R_ARM_THM_PC8          11   // Static Thumb16
#define R_ARM_BREL_ADJ         12   // Dynamic Data DeltaB(S) + A
#define R_ARM_TLS_DESC         13   // Dynamic Data
#define R_ARM_THM_SWI8         14   // Obsolete
#define R_ARM_XPC25            15   // Obsolete
#define R_ARM_THM_XPC22        16   // Obsolete
#define R_ARM_TLS_DTPMOD32     17   // Dynamic Data Module(S)
#define R_ARM_TLS_DTPOFF32     18   // Dynamic Data S + A - TLS
#define R_ARM_TLS_TPOFF32      19   // Dynamic Data S + A - tp
#define R_ARM_COPY             20   // Dynamic Misc
#define R_ARM_GLOB_DAT         21   // Dynamic Data (S + A) | T
#define R_ARM_JUMP_SLOT        22   // Dynamic Data (S + A) | T
#define R_ARM_RELATIVE         23   // Dynamic Data B(S) + A
#define R_ARM_GOTOFF32         24   // Static Data (((S + A) | T) - GOT_ORG)
#define R_ARM_BASE_PREL        25   // Static Data B(S) + A - P
#define R_ARM_GOT_BREL         26   // Static Data GOT(S) + A - GOT_ORG
#define R_ARM_PLT32            27   // Deprecated ARM ((S + A) | T) - P
#define R_ARM_CALL             28   // Static ARM ((S + A) | T) - P
#define R_ARM_JUMP24           29   // Static ARM ((S + A) | T) - P
#define R_ARM_THM_JUMP24       30   // Static Thumb32 ((S + A) | T) - P
#define R_ARM_BASE_ABS         31   // Static Data B(S) + A
#define R_ARM_ALU_PCREL_7_0    32   // Obsolete
#define R_ARM_ALU_PCREL_15_8   33   // Obsolete
#define R_ARM_ALU_PCREL_23_15  34   // Obsolete
#define R_ARM_LDR_SBREL_11_0_NC 35 // Deprecated ARM S + A - B(S)
#define R_ARM_ALU_SBREL_19_12_NC 36 // Deprecated ARM S + A - B(S)
#define R_ARM_ALU_SBREL_27_20_CK 37 // Deprecated ARM S + A - B(S)
#define R_ARM_TARGET1           38   // Data Misc (S + A) | T


#define STT_NOTYPE   0    // 未指定类型
#define STT_OBJECT   1    // 数据对象 (变量、数组等)
#define STT_FUNC     2    // 函数
#define STT_SECTION  3    // 节类型
#define STT_FILE     4    // 文件符号
#define STT_COMMON   5    // 公共数据对象
#define STT_TLS      6    // 线程局部存储对象

#define STB_LOCAL    0    // 本地符号
#define STB_GLOBAL   1    // 全局符号
#define STB_WEAK     2    // 弱符号

#define STV_DEFAULT   0    // 默认可见性
#define STV_INTERNAL  1    // 内部可见性
#define STV_HIDDEN    2    // 隐藏符号
#define STV_PROTECTED 3    // 受保护符号

#define SHN_UNDEF    0      // 未定义符号
#define SHN_ABS      0xFFF1 // 绝对值符号
#define SHN_COMMON   0xFFF2 // 公共符号


#endif //ELF_INTERNAL_H
