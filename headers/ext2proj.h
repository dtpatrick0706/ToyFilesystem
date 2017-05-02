#ifndef EXT2PROJ_H
#define EXT2PROJ_H

#include "ext2_fs.h"
#include "extra.h"

#define EXT2_NDIR_BLOCKS    12
#define EXT2_IND_BLOCK      EXT2_NDIR_BLOCKS
#define EXT2_DIND_BLOCK     (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK     (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS       (EXT2_TIND_BLOCK + 1)

/*
 * Structure of a directory entry
 */
#define EXT2_NAME_LEN 255

struct DirEntry {
  __u32 inode;      /* Inode number */
  __u16 rec_len;    /* Directory entry length */
  __u16 name_len;   /* Name length */
  char name[EXT2_NAME_LEN];  /* File name */
};

/*
 * The new version of the directory entry.  Since EXT2 structures are
 * stored in intel byte order, and the name_len field could never be
 * bigger than 255 chars, it's safe to reclaim the extra byte for the
 * file_type field.
 */
struct DirEntry2 {
  __u32 inode;      /* Inode number */
  __u16 rec_len;    /* Directory entry length */
  __u8  name_len;   /* Name length */
  __u8  file_type;
  char name[EXT2_NAME_LEN];  /* File name */
};
#endif
