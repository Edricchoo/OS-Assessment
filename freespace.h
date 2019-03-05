#pragma once
#define NUM_DIR 1 // define number of directory block
#define NUM_DATA 31 // define number of data block
#define NUM_ENTRIES 4 // define entries in a block

// Directory Structure =====================================================================
typedef struct directoryEntries {
	int index; // index of entry in directory block
	int blockNo; // current block number of directory entries
	int fileID; // file identifier
	int start; // starting block
	int end; // ending block
} DirectoryEntries;

typedef struct directory {
	DirectoryEntries directoryEntries[NUM_ENTRIES]; // number of entries in a directory block
} Directory;

typedef struct directoryNo {
	Directory directory[NUM_DIR]; // number of directory block
} DirectoryNo;

// Data Entries ============================================================================
typedef struct dataEntries{
	int index; // index of entry in data block (0-127)
	int blockNo; // current block number of data entries
	int entry; // input of entry in data block
	int jump; // jump entry for linked allocation
} DataEntries;

typedef struct data {
	DataEntries dataEntries[NUM_ENTRIES]; // number of entries in a data block
} Data;

typedef struct dataNo {
	Data data[NUM_DATA]; // number of data block
} DataNo;

// Free-space Management ==================================================================
typedef struct freeSpaceDirectoryEntries {
	int status; // 1: Full, 0: Available
} FreeSpaceDirectoryEntries;

typedef struct freeSpaceDirectory{
	FreeSpaceDirectoryEntries freeSpaceDirectoryEntries[NUM_ENTRIES];
} FreeSpaceDirectory;

typedef struct freeSpaceDirectoryNo{
	FreeSpaceDirectory freeSpaceDirectory[NUM_DIR]; // number of directory block to check free space
} FreeSpaceDirectoryNo;

typedef struct freeSpaceDataEntries {
	int status; // 1: Full, 0: Available
} FreeSpaceDataEntries;

typedef struct freeSpaceData {
	FreeSpaceDataEntries freeSpaceDataEntries[NUM_ENTRIES];
} FreeSpaceData;

typedef struct freeSpaceDataNo{
	FreeSpaceData freeSpaceData[NUM_DATA]; // number of data block to check free space
} FreeSpaceDataNo;

// method calling
int directoryCheck (FreeSpaceDirectoryNo *fsDirNo);
int freeSpaceCheck (FreeSpaceDataNo *fsDataNo);
int contiguousCheck (int num_of_block, FreeSpaceDataNo *fsData);
void startUp (/*Directory*/DirectoryNo *dir, /*Data*/DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);
void displayBlockInfo(DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);

/*
typedef struct freeSpaceDirectoryEntries {
	int status; // 1: allocated, 0: empty
} FreeSpaceDirectoryEntries;

typedef struct freeSpaceDataEntries {
	int status; // 1: allocated, 0: empty
} FreeSpaceDataEntries;
*/