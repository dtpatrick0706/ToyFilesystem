#include "ext2_fs.h"

const __u16 BOOT_SECTOR_MAGIC = 0xaa55;

struct PartitionEntry {
  __u8
    unused0[4],
    type,
    unused1[3];
  __u32
    firstSector,
    nSectors;
};

struct __attribute__((packed)) BootSector {
  __u8
    unused0[0x1be];
  PartitionEntry
    partitionTable[4];
  __u16
    magic;
};
 //current_bytes += bytes_read current_page++
