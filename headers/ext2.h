#ifndef EXT2_H
#define EXT2_H

#include "ext2_fs.h"
#include "vdi.h"
#include "boot.h"
//include "ext2proj.h"

class ext2 {
private:
  VDIClass* vdi;
  const static int EXT2_SUPER_BLOCK_OFFSET = 1024;
  struct BootSector mbr;

  unsigned int group_count;
  unsigned int sizeBlockGDescriptorTable;


public:
  ext2(VDIClass* vdic);
  struct ext2_group_desc* blockGDescriptorTable;
  struct ext2_super_block superblock;
  int ext2FirstSector_byte;
  long long blockGroupDescriptorTableLocation;


  char* getBlock(int blockNumber);
  char* getBlock(int blockNumber, int bytes);
  char* getBlock(int blockNumber, int bytes, int offsetBytes);
  ext2_super_block getSuperblock();
  int getFirstByte();

  struct ext2_inode getInode(int blockNumber, int inode);
  int verify_superblocks();
  int verify_blockgrouptables();
  int verify_inodes();
  int verify_directory();
  int verify_datablocks();
};
#endif
