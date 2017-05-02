#include "headers/ext2.h"
//#include "headers/vdi.h"
//#include "headers/extra.h"
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

ext2::ext2(VDIClass* vdic) : vdi(vdic){
// printf("nope");
  int arraySize = sizeof(BootSector);
  char* data = new char[arraySize];


  vdic->getBytes(data, 0, arraySize);
  std::memcpy(&mbr, data, arraySize);
  delete data;
  assert(mbr.magic == 0xaa55);
  //find ext2 partitionTable
  ext2FirstSector_byte = mbr.partitionTable[0].firstSector*vdic->header.sector_size;
  cout << "Ext2 First Sector Byte: " << ext2FirstSector_byte << endl;

  data = new char[sizeof(ext2_super_block)];
  vdic->getBytes(data, ext2FirstSector_byte + EXT2_SUPER_BLOCK_OFFSET, sizeof(ext2_super_block));
	std::memcpy(&superblock,data,sizeof(ext2_super_block));
	delete data;

  if(superblock.s_log_block_size >= 2){
    blockGroupDescriptorTableLocation = 1;
  }
  else{
    blockGroupDescriptorTableLocation = 2;
  }

  printf("Location of Block Desctiptor Table: %lli\n Block Size: %u\n Blocks Count: %u\nBlocks Per Group: %u\nSize Groupdesc: %lu\n",
      blockGroupDescriptorTableLocation,
      superblock.s_log_block_size,
      superblock.s_blocks_count,
      superblock.s_blocks_per_group,
      sizeof(ext2_group_desc));

  group_count = 1 + (superblock.s_blocks_count - 1) / superblock.s_blocks_per_group;
  sizeBlockGDescriptorTable = sizeof(ext2_group_desc) * group_count;

  printf("Number of Block Groups: %i\nSize of Block G Descriptor Table: %i\n", group_count, sizeBlockGDescriptorTable );
}

char* ext2::getBlock(int blockNumber){
  char* data = new char[1024 << superblock.s_log_block_size];
  vdi->getBytes(data, (blockNumber * (1024 << superblock.s_log_block_size)) + ext2FirstSector_byte, (1024 << superblock.s_log_block_size));
  return data;
}

char* ext2::getBlock(int blockNumber, int bytes){
  char* data = new char[bytes];
  vdi->getBytes(data, (blockNumber * (1024 << superblock.s_log_block_size)) + ext2FirstSector_byte, bytes);
}

char* ext2::getBlock(int blockNumber, int bytes, int offsetBytes)
{
	char* data = new char[bytes];
	vdi->getBytes(data, (blockNumber * ( 1024 << superblock.s_log_block_size)) + ext2FirstSector_byte + offsetBytes, bytes);
	return data;
}

ext2_super_block ext2::getSuperblock(){
  return superblock;
}

int ext2::getFirstByte(){
  return ext2FirstSector_byte;
}
