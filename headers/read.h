#include <cstdint>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "superblock.h"
#include "groupdesc.h"
#include "inode.h"
#include "directory.h"
#include "extras.h"

using namespace std;

	int read_vdiheader(int file, vdi_header &header);

	int read_vdimap(int file, vdi_header header, __u32 map[], __u32 blocks_in_hdd);

	int read_MBR(int file, vdi_header header, BootSector &boot);

	int read_superblock(int file, vdi_header header, BootSector boot, __u32 map[], ext2_super_block &super);

	int read_group_decsriptor_list(int filedesc, vdi_header vdi_head, BootSector boot_sector, __u32 vdimap[], __u32 block_size,
		ext2_group_desc group_desc_table[], __u32 num_block_groups);

	__u8* read_bitmap(__u32 block_size, __u32 block_id, int filedesc, vdi_header vdi_head, BootSector boot_sector, __u32 vdimap[]);

	ext2_inode read_inode(__u32 inode_no, __u32 block_size, ext2_super_block super_block, ext2_group_desc group_desc_table[],
		int filedesc, vdi_header vdi_head, BootSector boot_sector, __u32 vdimap[]);

	bool fetch_directory_entry(ext2_dir_entry_2 &found_entry, __u8 *data_block, __u32 size_diff, string filename, bool print);

	int blockread(ext2_inode inode, __u32 block_num, __u32 block_size, __u8 *buffer,
		int filedesc, vdi_header vdi_head, BootSector boot_sector, __u32 vdimap[]);
