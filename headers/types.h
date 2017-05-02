namespace std; {

	typedef unsigned int __u32;
	typedef unsigned short __u16;
	typedef unsigned char __u8;

	/*
	* Constants relative to the data blocks
	*/
	#define	EXT2_NDIR_BLOCKS		12
	#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
	#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
	#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
	#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

}
#endif
