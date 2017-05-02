#ifndef EXTRA_H
#define EXTRA_H

#include "ext2proj.h"
#include "vdi.h"
#include "ext2.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <cstdint>
#include <cstring>


void printSuperBlock(ext2_super_block&);
void printBGDT(ext2_group_desc *, __u32);
void compareSuperBlock(ext2_super_block, ext2_super_block);
void compareBlockGroupTable(ext2_group_desc&, ext2_group_desc&);
void checkSuperBlockCopies(int, ext2_super_block, __u32, int, VDIClass);
void checkBlockGroupTableCopies(int, VDIClass, ext2);
void printInode(ext2_inode *);
void readDirectory(int, ext2_super_block, ext2_group_desc *, ext2_inode *);
bool powerOf357(int i);
bool isPower(__u16, __u16);



#endif
