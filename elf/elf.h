#ifndef ELF_ELF_H
#define ELF_ELF_H

#include "internal.h"
#include <stdbool.h>
#include <stdio.h>
#include "elf32.h"
#include "elf64.h"

// 判断给定的文件是不是ELF64，若为ELF64则返回true，为ELF32则返回false，其他情况则直接报错
bool is_64bits(FILE *file);

#endif //ELF_ELF_H
