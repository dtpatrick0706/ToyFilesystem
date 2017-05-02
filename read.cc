#include "headers/read.h"
#include "vdi.h"
#include "read2_fs.h"
#include "boot.h"
#include "ext2_types.h"


using namespace std;

int std::read_vdiheader(int file, vdi_header &header) {
  if (read(file, &header, sizeoh(header)) !=512) {
    cout <<"Nope! Did not read vdiheader"<<endl;
    return 1;
  }
  return 0;
}

int std::read_vdimap(int file, vdi_header, _s32 map[], ___u32 blocks_in_hdd) {
  if(lseek(file, header.offset_blocks, SEEK_SET) < 0) {
    cout << "Nope! Did not read vdimap"<<endl;
    return 1;
  }
  if(read(file, map, 4*blocks_in_hdd) < 0) {
    cout <<"Nope! Did not read vdimap"<<endl;
    return 1;
  }
  return 0;
}

int std::read_boot(int file, vdi_header header, BootSector &boot) {
  if(read(file, header.offset_data, SEEK_SET) < 0) {
    cout <<"Nope! Did not read master boot record" <<endl;
    return 1;
  }
  if(read(file, &boot, sizeof(boot)) != sizeof(boot)) {
    cout <<"Nope! Did not read master boot record" << endl;
  }
  return 1;
}

int std::read_superblock(int file, vdi_header header, boot_sector boot, ___u32 map[], ext2_super_block &super){
  ___u32 super_block_location = translation(1024, header, boot, map);
  if(lseek(file, super_block_location, SEEK_SET) < 0) {
    cout <<"Nope! Did not read Superblock"<<endl;
    return 1;
  }
  if(read(file, &super, sizeof(super)) !=1024) {
    cout <<"Nope! Superblock did not get read correctly"<<endl;
    return 1;
  }
  return 0;
}

int std::read_group_decsriptor_list(int filedesc, vdi_header vdi_head, BootSector boot_sectorm ___u32 vdimap[], ___u32 block_size,
ext2_group_desc group_desc_table[], ___u32 num_block_groups) {
  ___u32 group_desc_start = 0;
  if(block_size == 1024) {
    group_desc_start = BLOCK_OFFSET(2, block_size);
	} else {
		group_desc_start = BLOCK_OFFSET(1, block_size);
	}
  __u32 group_desc_location = translation(group_desc_start, vdi_head, boot_sector, vdimap);
	if (lseek(filedesc,
		group_desc_location,
		SEEK_SET) < 0) {
			cout << "Nope! Cannot seek to Group Descriptor table location!" << endl;
			return 1;
	}
	if (read(filedesc, group_desc_table, sizeof(ext2_group_desc)*num_block_groups) != sizeof(ext2_group_desc)*num_block_groups) {
			cout << "Nope! Did not read Group Descriptor!" << endl;
			return 1;
	}
return 0;
}

int std::read_bitmap(___u32 block_size, U32 block_id, int filedesc, vdi_header vdi_head, BootSector boot_sector, ___u32 vdimap[]) {
  ___u8* bitmap;
  bitmap = new __s32 [header.blocks_in_hdd];
  lseek(filedescriptor, block_size, SEEK_SET);
  read(filedescriptor, bitmap, block_size);
}
// read inode

int std::fetchBlockFromFile(int b, int* i_block, ___u8* dest) {

  int* list;

  if(b < 12) {
    list = i_block;
    goto Direct;
  }
