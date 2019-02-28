#include <stdio.h>
#include "freespace.h"

int directoryCheck (Directory dir, FreeSpaceDirectoryNo fsDirNo) {
    int i,j;

	// loop thru all directory blocks
    for (i = 0; i < NUM_DIR; i++) {
		// loop thru all entries in directory blocks
		for (j = 0; j < NUM_ENTRIES; j++) {

			// if status = 0; empty, and fileID = -1; still no filled, return current block and state it's available 
			if (fsDirNo.freeSpaceDirectory[j].status == 0 && dir.directoryEntries[j].fileID == -1) {
            return i;
			}
        }
    }
    return -1; // not enough space
}

int freeSpaceCheck (FreeSpaceDataNo fsDataNo) {
    int i;
	
	// loop through all blocks and find next available blocks
    for (i = 0; i < NUM_DATA; i++) {
        if (fsDataNo.freeSpaceData[i].status == 0) {
            return (i + NUM_DIR);
        }
    }
    return -1; // not enough space
}

int contiguousCheck (int num_of_block, FreeSpaceDataNo fsDataNo) {
    int i,j;

	// loop thru all data blocks
    for (i = 0; i < NUM_DATA; i++) {

		// loop through and find consecutive
        for (j = 0; j < num_of_block; j++) {
            if (fsDataNo.freeSpaceData[i+j].status == 1) {
                break;
            }
        }
		// if the next amount of num_of_block is valid, return starting from which block to get the consecutive num_of_block
        if (j == num_of_block) {
            return (i + NUM_DIR);
        }
    }
    return -1; // not enough space
}

void startUp (Directory *dir, Data *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo) {
	int i,j;
	
	// loop thru all dir blocks
	for (i = 0; i < NUM_DIR; i++) {
		fsDirNo->freeSpaceDirectory[i].status = 0; // initialze all dir block to empty
		
		// loop thru thru all entries in the data block
		for (j =0; j < NUM_ENTRIES; j++) {
			dir->directoryEntries[j].fileID = -1; // intiailize file identifier
			dir->directoryEntries[j].start = -1; // intiailize starting block
			dir->directoryEntries[j].end = -1; // intiailize ending block
		}
	}

	// loop thru all data blocks
	for (i = 0; i < NUM_DATA; i++ ) {
		fsDataNo->freeSpaceData[i].status = 0; // initialze all data block to empty
		
		// loop thru thru all entries in the data block
		for (j = 0; j < NUM_ENTRIES; j++) {
			data->dataEntries[j].entry = -1; // intiailize entry to -1
		}	
	}
}

void displayBlockInfo(Directory dir, Data data) {
	int i;
	int blockCount = 0;
	int indexCount = 0;
	
	// loop thru thru all dir block
	for (blockCount =0; blockCount < NUM_DIR; blockCount++){
		// loop thru thru all entries in the dir block
		for (i =0; i < NUM_ENTRIES; i++) {
			dir.directoryEntries[i].index = indexCount; // intiailize count for index
			dir.directoryEntries[i].blockNo = blockCount; // intiailize count for block
			printf("Index: %d | Block: %d | File Content: %d %d %d\n", indexCount, blockCount, dir.directoryEntries[i].fileID, dir.directoryEntries[i].start, dir.directoryEntries[i].end);
			indexCount++;		
		}
	}
	printf("===============================================================================\n");
	
	// loop thru thru all data block
	for (; blockCount <= NUM_DATA; blockCount++) {
		// loop thru thru all entries in the data block
		for (i =0; i < NUM_ENTRIES; i++) {
			data.dataEntries[i].index = indexCount; // intiailize count for index
			data.dataEntries[i].blockNo= blockCount; // intiailize count for block
			printf("Index: %d | Block: %d | File Content: %d\n", indexCount, blockCount, data.dataEntries[i].entry); 
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