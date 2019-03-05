#include <stdio.h>
#include "freespace.h"

int directoryCheck (FreeSpaceDirectoryNo *fsDirNo) {
    int i,j;

	// loop thru all directory blocks
    for (i = 0; i < NUM_DIR; i++) {
		// loop thru all entries in directory blocks
		for (j = 0; j < NUM_ENTRIES; j++) {
			//printf("i: %d | j: %d\n",i,j);
			if (fsDirNo->freeSpaceDirectory[i].freeSpaceDirectoryEntries[j].status == 0){
				return j;
			}
        }
    }
    return -1; // not enough space
}

int freeSpaceCheck (FreeSpaceDataNo *fsDataNo) {
    int i, j;
	
	// loop through all blocks and find next available blocks
	for (i = 0; i < NUM_DATA; i++) {
		for (j = 0; j < NUM_ENTRIES; j++){
			if (fsDataNo->freeSpaceData[i].freeSpaceDataEntries[j].status == 0) {
				return j;
			}
		}
		return -1; // not enough space
	}
}

int contiguousCheck (int num_of_block, FreeSpaceDataNo *fsDataNo) {
    int i,j,count=0;

	// loop thru all data blocks
    for (i = 0; i < NUM_DATA; i++)
    {
    	for (j = 0; j < num_of_block; j++)
		{
    		if (fsDataNo->freeSpaceData[i + j].freeSpaceDataEntries[0].status == 1)
			{
    			break;
			}
			else if (j == (num_of_block - 1))
			{
				return i;
			}
		}
    }
    return -1; // not enough space
}

void startUp (DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo) {
	int i,j;

	// loop thru all dir blocks
	for (i = 0; i < NUM_DIR; i++) {
		// loop thru thru all entries in the data block
		for (j =0; j < NUM_ENTRIES; j++) {
			dir->directory[i].directoryEntries[j].fileID = -1; // intiailize file identifier
			dir->directory[i].directoryEntries[j].start = -1; // intiailize starting block
			dir->directory[i].directoryEntries[j].end = -1; // intiailize ending block
			fsDirNo->freeSpaceDirectory[i].freeSpaceDirectoryEntries[j].status = 0; // initialze all dir block to empty
		}
	}

	// loop thru all data blocks
	for (i = 0; i < NUM_DATA; i++ ) {
		// loop thru thru all entries in the data block
		for (j = 0; j < NUM_ENTRIES; j++) {
			data->data[i].dataEntries[j].entry = -1; // initialize entry to -1
			fsDataNo->freeSpaceData[i].freeSpaceDataEntries[j].status = 0; // initialze all data block to empty
		}	
	}
}

void displayBlockInfo(DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo) {
	int i, j;
	int indexCount = 0;
	printf("===============================================================================\n");
	// loop thru thru all entries in the dir block
	for(i = 0; i < NUM_DIR; i++) {
		for (j = 0; j < NUM_ENTRIES; j++) {
		dir->directory[i].directoryEntries[j].index = indexCount; // intiailize count for index
		dir->directory[i].directoryEntries[j].blockNo = i; // intiailize count for block
		printf("Index: %d | Block: %d | File Content: %d %d %d | Status: %d\n", indexCount, i, dir->directory[i].directoryEntries[j].fileID, dir->directory[i].directoryEntries[j].start, dir->directory[i].directoryEntries[j].end, fsDirNo->freeSpaceDirectory[i].freeSpaceDirectoryEntries[j].status);
		indexCount++;
		}
	}
	printf("===============================================================================\n");
	
	// loop thru thru all data block
	for (i = 0; i < NUM_DATA; i++) {
		// loop thru thru all entries in the data block
		for (j = 0; j < NUM_ENTRIES; j++) {
			//printf("i: %d | j: %d\n", i, j);
			data->data[i].dataEntries[j].index = indexCount; // intiailize count for index
			data->data[i].dataEntries[j].blockNo = i; // intiailize count for block
			printf("Index: %d | Block: %d | File Content: %d | Status: %d\n" , indexCount, i+NUM_DIR, data->data[i].dataEntries[j].entry, fsDataNo->freeSpaceData[i].freeSpaceDataEntries[j].status);
			indexCount++;
		}
	}
}

/*
debug; printf lines
====================================================================
printf("File Content: %d %d %d\n", dir->directoryEntries[j].fileID, dir->directoryEntries[j].start, dir->directoryEntries[j].end); // debug; to print content
printf("Block: %d | File Content: %d\n",i, data->dataEntries[j].entry); // debug; to print content
printf("%d, %d\n", fsDirNo.freeSpaceDirectory[i].status,i); // debug; to print status in directory blocks
printf("%d, %d\n", fsDataNo.freeSpaceData[i].status,i); // debug; to print status in data blocks
====================================================================

debug; test freespace status
====================================================================
for (i = 0; i < 3; i++){
	fsDirNo.freeSpaceDirectory[i].status = 1;
	dir.directoryEntries[i].fileID = 100;
}

for (i = 0; i < 3; i++){
	fsDataNo.freeSpaceData[i].status = 1;
}

for (i = 2; i < 5; i++) {
	fsDataNo.freeSpaceData[i].status = 1;
}
====================================================================
*/