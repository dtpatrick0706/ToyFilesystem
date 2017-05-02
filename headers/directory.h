#include "types.h"

namespace std {

	struct __attribute__((packed)) ext2_dir_entry_2 {
		__u32	inode;			/* Inode number */
		__u16	rec_len;		/* Directory entry length */
		__u8	name_len;		/* Name length */
		__u8	file_type;
		__u8	name[255];			/* File name, up to EXT2_NAME_LEN */
	};
}
#endif
