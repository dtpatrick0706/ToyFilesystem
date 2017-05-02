#ifndef PROJECT_GROUPDESC
#define PROJECT_GROUPDESC
#include "types.h"

namespace os_term_project {
	/*
	* Structure of a blocks group descriptor
	*/
	struct __attribute__((packed)) ext2_group_desc {
		__u32	bg_block_bitmap;		/* Blocks bitmap block */
		__u32	bg_inode_bitmap;		/* Inodes bitmap block */
		__u32	bg_inode_table;		/* Inodes table block */
		__u16	bg_free_blocks_count;	/* Free blocks count */
		__u16	bg_free_inodes_count;	/* Free inodes count */
		__u16	bg_used_dirs_count;	/* Directories count */
		__u16	bg_pad;
		__u32	bg_reserved[3];
	};
}
#endif
