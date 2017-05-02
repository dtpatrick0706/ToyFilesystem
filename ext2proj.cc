#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
//#include "headers/ext2proj.h"
#include "headers/extra.h"
#include "headers/vdi.h"
//#include "headers/ext2.h"

using namespace std;



int main(int argc, char *argv[]) {
  ext2_super_block sb;
  ext2_inode inode;
  __u16 blockSize;

  char pathname[280] = "Test-fixed-1k.vdi";
  int fs = open(pathname,O_RDONLY);

  assert(fs != 0);

  VDIClass vdi(fs);
  ext2 ext2Partition(&vdi);
  std::cout << vdi.getBlockSize() << std::endl;



  // check if magic number is correct (0xEF53)
  printSuperBlock(ext2Partition.superblock);
  assert(ext2Partition.superblock.s_magic == 0xEF53);
  blockSize = 1024 << ext2Partition.superblock.s_log_block_size;
  // filesystem specs
  __u32 fsSize = ext2Partition.superblock.s_blocks_count * blockSize;
  printf("\nTotal size of filesystem:    %u bytes\n", fsSize);
  __u32 freeSpace = blockSize * ext2Partition.superblock.s_free_blocks_count;
  printf("Free space:                   %u bytes\n", freeSpace);
  __u32 usedSpace = blockSize * (ext2Partition.superblock.s_blocks_count - ext2Partition.superblock.s_free_blocks_count);
  printf("Used space:                   %u bytes\n", usedSpace);

  __u32 totalBlockGroups = ceil(ext2Partition.superblock.s_blocks_count / ext2Partition.superblock.s_blocks_per_group);
  int blockGroups = (ext2Partition.superblock.s_blocks_count + ext2Partition.superblock.s_blocks_per_group -1) / ext2Partition.superblock.s_blocks_per_group;
   char* blocks = new char[sizeof(ext2_group_desc)];
   vdi.getBytes(blocks, (ext2Partition.blockGroupDescriptorTableLocation * (1024 << ext2Partition.superblock.s_log_block_size)) + ext2Partition.ext2FirstSector_byte, (1024 << ext2Partition.superblock.s_log_block_size));
   ext2Partition.blockGDescriptorTable = (ext2_group_desc *) blocks;

  __u16 inodeNumber = 2;
  __u32 blockGroup = (inodeNumber - 1) / ext2Partition.superblock.s_inodes_per_group;
  __u32 inodeIndex = (inodeNumber - 1) % ext2Partition.superblock.s_inodes_per_group;
  __u32 containingBlock = (inodeIndex * sizeof(ext2_inode)) / blockSize;
  lseek(fs, blockSize + 1024 * ((ext2Partition.blockGDescriptorTable[blockGroup].bg_inode_table) - 1)
        + inodeIndex * sizeof(ext2_inode), SEEK_SET);
  read(fs, &inode, sizeof(ext2_inode));


  printSuperBlock(ext2Partition.superblock);
  printBGDT(ext2Partition.blockGDescriptorTable, totalBlockGroups);
  checkSuperBlockCopies(fs, ext2Partition.superblock, totalBlockGroups, ext2Partition.ext2FirstSector_byte, vdi);
  //checkBlockGroupTableCopies(fs, vdi, ext2Partition);
  printInode(&inode);

  //readDirectory(fs, ext2Partition.superblock, ext2Partition.blockGDescriptorTable, &inode);
  close(fs);
  return 0;
}
