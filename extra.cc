#include "headers/extra.h"
#include <iostream>

void printSuperBlock(ext2_super_block &sb) {
  printf("\nSuperblock from block group %i\n", sb.s_block_group_nr);
  printf("Inodes count:          %15u\n"
         "Blocks count:          %15u\n"
         "Reserved blocks count: %15u\n"
         "Free blocks count:     %15u\n"
         "Free inodes count:     %15u\n"
         "State:                 %15u\n"
         "Block per group:       %15u\n"
         "Magic number:          %15x\n\n",
         sb.s_inodes_count,
         sb.s_blocks_count,
         sb.s_r_blocks_count,
         sb.s_free_blocks_count,
         sb.s_free_inodes_count,
         sb.s_state,
         sb.s_blocks_per_group,
         sb.s_magic);
}

void printBGDT(ext2_group_desc *bg, __u32 totalBlockGroups) {
  printf("Group    Block     Inode      Inode    Free      Free        Used\n"
         "         Bitmap    Bitmap     Table    Blocks    Inodes      Dirs\n"
         "-----------------------------------------------------------------\n");
  for (int i = 0; i <= totalBlockGroups; i++) {
    printf("%5d %9u %9u %9u %9u %9u %9u\n",
           i,
           bg[i].bg_block_bitmap,
           bg[i].bg_inode_bitmap,
           bg[i].bg_inode_table,
           bg[i].bg_free_blocks_count,
           bg[i].bg_free_inodes_count,
           bg[i].bg_used_dirs_count);
  }
  printf("\n");
}

//
// compares the original master superblock with the copies
// attempts to correct if the copies have been corrupted
//
void compareSuperBlock(ext2_super_block sb, ext2_super_block sbCopy) {
  if (sb.s_inodes_count != sbCopy.s_inodes_count) {
    printf("Error: s_inodes_count\n");
    sbCopy.s_inodes_count = sb.s_inodes_count;
  }
  if (sb.s_blocks_count != sbCopy.s_blocks_count) {
    printf("Error: s_blocks_count \n");
    sbCopy.s_blocks_count = sb.s_blocks_count;
  }
  if (sb.s_r_blocks_count != sbCopy.s_r_blocks_count) {
    printf("Error: s_r_blocks_count \n");
    sbCopy.s_r_blocks_count = sb.s_r_blocks_count;
  }
  if (sb.s_free_blocks_count != sbCopy.s_free_blocks_count) {
    printf("Error: s_free_blocks_count \n");
  }
  if (sb.s_free_inodes_count != sbCopy.s_free_inodes_count) {
    printf("Error: s_free_inodes_count \n");
  }
  if (sb.s_first_data_block != sbCopy.s_first_data_block) {
    printf("Error: s_first_data_block \n");
    sbCopy.s_first_data_block = sb.s_first_data_block;
  }
  if (sb.s_log_block_size != sbCopy.s_log_block_size) {
    printf("Error: s_log_block_size \n");
    sbCopy.s_log_block_size = sb.s_log_block_size;
  }
  // if (sb.s_log_frag_size != sbCopy.s_log_frag_size) {
  //   printf("Error: s_log_frag_size \n");
  //   sbCopy.s_log_frag_size = sb.s_log_frag_size;
  // }
  if (sb.s_blocks_per_group != sbCopy.s_blocks_per_group) {
    printf("Error: s_blocks_per_group \n");
    sbCopy.s_blocks_per_group = sb.s_blocks_per_group;
  }
  // if (sb.s_frags_per_group != sbCopy.s_frags_per_group) {
  //   printf("Error: s_frags_per_group \n");
  //   sbCopy.s_frags_per_group = sb.s_frags_per_group;
  // }
  if (sb.s_inodes_per_group != sbCopy.s_inodes_per_group) {
    printf("Error: s_inodes_per_group \n");
    sbCopy.s_inodes_per_group = sb.s_inodes_per_group;
  }
  if (sb.s_mtime != sbCopy.s_mtime) {
    printf("Error: s_mtime \n");
    sbCopy.s_mtime = sb.s_mtime;
  }
  if (sb.s_wtime != sbCopy.s_wtime) {
    printf("Error: s_wtime \n");
  }
  if (sb.s_mnt_count != sbCopy.s_mnt_count) {
    printf("Error: s_mnt_count \n");
  }
  if (sb.s_max_mnt_count != sbCopy.s_max_mnt_count) {
    printf("Error: s_max_mnt_count \n");
    sbCopy.s_max_mnt_count = sb.s_max_mnt_count;
  }
  if (sb.s_magic != sbCopy.s_magic) {
    printf("Error: s_magic \n");
    sbCopy.s_magic = sb.s_magic;
  }
  if (sb.s_state != sbCopy.s_state) {
    printf("Error: s_state \n");
  }
  if (sb.s_errors != sbCopy.s_errors) {
    printf("Error: s_errors \n");
    sbCopy.s_errors = sb.s_errors;
  }
  if (sb.s_minor_rev_level != sbCopy.s_minor_rev_level) {
    printf("Error: s_minor_rev_level \n");
    sbCopy.s_minor_rev_level = sb.s_minor_rev_level;
  }
  if (sb.s_lastcheck != sbCopy.s_lastcheck) {
    printf("Error: s_lastcheck \n");
    sbCopy.s_lastcheck = sb.s_lastcheck;
  }
  if (sb.s_checkinterval != sbCopy.s_checkinterval) {
    printf("Error: s_checkinterval \n");
    sbCopy.s_checkinterval = sb.s_checkinterval;
  }
  if (sb.s_creator_os != sbCopy.s_creator_os) {
    printf("Error: s_creator_os \n");
    sbCopy.s_creator_os = sb.s_creator_os;
  }
  if (sb.s_rev_level != sbCopy.s_rev_level) {
    printf("Error: s_rev_level \n");
    sbCopy.s_rev_level = sb.s_rev_level;
  }
  if (sb.s_def_resuid != sbCopy.s_def_resuid) {
    printf("Error: s_def_resuid \n");
    sbCopy.s_def_resuid = sb.s_def_resuid;
  }
  if (sb.s_def_resgid != sbCopy.s_def_resgid) {
    printf("Error: s_def_resgid \n");
    sbCopy.s_def_resgid = sb.s_def_resgid;
  }
  if (sb.s_first_ino != sbCopy.s_first_ino) {
    printf("Error: s_first_ino \n");
    sbCopy.s_first_ino = sb.s_first_ino;
  }
  if (sb.s_inode_size != sbCopy.s_inode_size) {
    printf("Error: s_inode_size \n");
    sbCopy.s_inode_size = sb.s_inode_size;
  }
  if (sb.s_block_group_nr != sbCopy.s_block_group_nr) {
    printf("Error: s_block_group_nr \n");
  }
  if (sb.s_feature_compat != sbCopy.s_feature_compat) {
    printf("Error: s_feature_compat \n");
    sbCopy.s_feature_compat = sb.s_feature_compat;
  }
  if (sb.s_feature_incompat != sbCopy.s_feature_incompat) {
    printf("Error: s_feature_incompat \n");
    sbCopy.s_feature_incompat = sb.s_feature_incompat;
  }
  if (sb.s_feature_ro_compat != sbCopy.s_feature_ro_compat) {
    printf("Error: s_feature_ro_compat \n");
    sbCopy.s_feature_ro_compat = sb.s_feature_ro_compat;
  }
}

//
// compares the original block group table with the copies
// attempts to correct if the copies have been corrupted
//
void compareBlockGroupTable(ext2_group_desc &bg, ext2_group_desc &bgCopy) {
  if (bg.bg_block_bitmap != bgCopy.bg_block_bitmap) {
    printf("Error: bg_block_bitmap \n");
    bgCopy.bg_block_bitmap = bg.bg_block_bitmap;
  }
  if (bg.bg_inode_bitmap != bgCopy.bg_inode_bitmap) {
    printf("Error: bg_inode_bitmap \n");
    bgCopy.bg_inode_bitmap = bg.bg_inode_bitmap;
  }
  if (bg.bg_inode_table != bgCopy.bg_inode_table) {
    printf("Error: bg_inode_table \n");
    bgCopy.bg_inode_table = bg.bg_inode_table;
  }
  if (bg.bg_free_blocks_count != bgCopy.bg_free_blocks_count) {
    printf("Error: bg_free_blocks_count \n");
    bgCopy.bg_free_blocks_count = bg.bg_free_blocks_count;
  }
  if (bg.bg_free_inodes_count != bgCopy.bg_free_inodes_count) {
    printf("Error: bg_free_inodes_count \n");
    bgCopy.bg_free_inodes_count = bg.bg_free_inodes_count;
  }
  if (bg.bg_used_dirs_count != bgCopy.bg_used_dirs_count) {
    printf("Error: bg_used_dirs_count \n");
    bgCopy.bg_used_dirs_count = bg.bg_used_dirs_count;
  }
}


void checkSuperBlockCopies(int fs, ext2_super_block sb, __u32 totalBlockGroups, int ext2FirstSector_byte, VDIClass vdi) {
  ext2_super_block sbCopy;
  __u32 blocksPerGroup = sb.s_blocks_per_group;
  __u32 blockSized = 1024 << sb.s_log_block_size;
  char* data = new char[sizeof(ext2_super_block)];
  printf("----------------------------");
  printf("\nTesting Superblock copies...\n");
  printf("----------------------------");
  for (__u32 i = 0; i < totalBlockGroups; i++) {
    if (powerOf357(i)) {
      printf("\nBlock group: %i\n", i);
      __u32 offset = 0;
      //std::cout << blockSized << std::endl;
      if (i == 0 || blockSized - 1){

           offset = 1024;
       }
      char* data = new char[sizeof(ext2_super_block)];
      vdi.getBytes(data, ((i * blocksPerGroup) * blockSized) + ext2FirstSector_byte + offset, sizeof(ext2_super_block));
      std::memcpy(&sbCopy, data, sizeof(ext2_super_block));
      printSuperBlock(sbCopy);
      delete data;
      compareSuperBlock(sb, sbCopy);
    }
  }
}

void checkBlockGroupTableCopies(int fs, VDIClass vdi, ext2 ext2Part) {
  __u32 blockSized = 1024 << ext2Part.superblock.s_log_block_size;
  __u32 blocksPerGroup = ext2Part.superblock.s_blocks_per_group;
  __u32 totalBlockGroups = ceil(ext2Part.superblock.s_blocks_count / ext2Part.superblock.s_blocks_per_group);
  std::cout << "hello" << std::endl;
  char* blocks = new char[sizeof(ext2_group_desc)];
  vdi.getBytes(blocks, (ext2Part.blockGroupDescriptorTableLocation * (1024 << ext2Part.superblock.s_log_block_size)) + ext2Part.ext2FirstSector_byte, (1024 << ext2Part.superblock.s_log_block_size));
  ext2_group_desc *bgCopy = (ext2_group_desc *) blocks;
  printf("\n----------------------------------");
  printf("\nTesting Block Group copies...\n");
  printf("----------------------------------");
  for (int i = 0; i < totalBlockGroups; i++) {
    if (powerOf357(i)) {
      printf("\nBlock group: %i\n", i);
      if (blockSized == 1024) {
        lseek(fs, (i * 32) * blockSized * blocksPerGroup + 2048, SEEK_SET);
      } else {
        lseek(fs, (i * 32) * blockSized * blocksPerGroup + blockSized, SEEK_SET);
      }
      for (int j = 0; j < totalBlockGroups; j++) {
        read(fs, &bgCopy[j], sizeof(ext2_group_desc));
        compareBlockGroupTable(ext2Part.blockGDescriptorTable[j], bgCopy[j]);
      }
    }
  }
}

void printInode(ext2_inode *inode) {
  printf("\nReading root inode (2)\n"
         "Owner UID:  %5hu\n"
         "Size:       %5u bytes\n"
         "1/2K Blocks:%5u\n"
         "Ref count:  %5u\n",
         inode->i_uid,
         inode->i_size,
         inode->i_blocks,
         inode->i_links_count);

  for (int i = 0; i < EXT2_N_BLOCKS; i++) {
    // direct blocks (entries 1-12)
    if (i < EXT2_NDIR_BLOCKS) {
      printf("Block %2u:   %5u\n", i, inode->i_block[i]);
    }
    // single indirect (13th entry)
    else if (i == EXT2_IND_BLOCK) {
      printf("Single:     %5u\n", inode->i_block[i]);
    }
    // double indirect (14th entry)
    else if (i == EXT2_DIND_BLOCK) {
      printf("Double:     %5u\n", inode->i_block[i]);
    }
    // triple indirect (15th entry)
    else if (i == EXT2_TIND_BLOCK) {
      printf("Triple:     %5u\n\n", inode->i_block[i]);
    }
  }
}

//
// Note: couldn't get this to work, but I feel I'm on the right track
//
void readDirectory(int fs, ext2_super_block sb, ext2_group_desc *bg, ext2_inode *inode, __u32 blockSize) {
  char *block[blockSize];
  DirEntry2 *de;
  __u16 cursor;

  lseek(fs, blockSize * (inode->i_block[0]), SEEK_SET);
  read(fs, block, blockSize);
  printf("Directory contents: \n");
  printf("----------------------------------");
  // print out directory
  de = (DirEntry2 *) block;  // first entry
  while (cursor < inode->i_size) {
    if (de->inode > 0) {
      // print out info on this entry
      char fileName[EXT2_NAME_LEN + 1];
      memcpy(fileName, de->name, de->name_len);
      fileName[de->name_len] = '\0'; // append null to the file name
      printf("Inode: %6d %20s\n", de->inode, fileName);
    }
    // move on to next entry in this directory
    de += de->rec_len;
    cursor += de->rec_len;
  }
 // free(block);
}
/*
void fetchBlockFromFile(int b, int *i_block, __u8 *dest){
  int *list;
  if(b<12){
    list=i_block;
    goto direct;
  }
  else if(b<12+apb){
    list = i_block +12;
    b-=12;
    goto single;
  }
  else if(b<12+apb*(1+apb)){
    list=i_block+13;
    b-=12+apb;
    goto double;
  }
  else{
    fetchBlock(i_block[14]);
    b-=12+apb*(1+apb);
  }
  double:
    fetchBlock(list[b/apb/apb],temp);
    list = temp;
    b %= apb * apb;
  single:
    fetchBlock(list[b/abp], temp);
    list = temp;
    b %= apb;
  direct:
    fetchBlock(list[b],dest);
}
*/
bool powerOf357(int i){
  if(isPower(i, 3)){
    return true;
  }
  else if(isPower(i, 5)){
    return true;
  }
  else if(isPower(i, 7)){
    return true;
  }
  else{
    return false;
  }
}
bool isPower(__u16 x, __u16 y) {
  while (x > 1) {
    if (x % y != 0) {
      return false;
    }
    x /= y;
  }
  return true;
}
