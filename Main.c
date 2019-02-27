#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freespace.h"

void display_block_info() {
	int i;
	int blockCount = 0;
	int indexCount = 0;
	Directory dir; // create a directory structure
	Data data; // create a data structure
	
	for (blockCount =0; blockCount < NUM_DIR; blockCount++){
		for (i =0; i < NUM_ENTRIES; i++) {
			dir.directoryEntries[i].index = indexCount; // intiailize count for index
			dir.directoryEntries[i].blockNo = blockCount; // intiailize count for block
			dir.directoryEntries[i].fileID = -1; // intiailize file identifier
			dir.directoryEntries[i].start = -1; // intiailize starting block
			dir.directoryEntries[i].end = -1; // intiailize ending block

			printf("Index: %d | Block: %d | File Content: %d %d %d\n", indexCount, blockCount, dir.directoryEntries[i].fileID, dir.directoryEntries[i].start, dir.directoryEntries[i].end);
			indexCount++;		
		}
	}
	printf("===============================================================================\n"); // debug; line to seperate Directory and Data block

	for (; blockCount <= NUM_DATA; blockCount++) {
		for (i =0; i < NUM_ENTRIES; i++) {
			data.dataEntries[i].index = indexCount; // intiailize count for index
			data.dataEntries[i].blockNo= blockCount; // intiailize count for block
			data.dataEntries[i].entry = -1; // intiailize entry
			printf("Index: %d | Block: %d | File Content: %d\n", indexCount, blockCount, data.dataEntries[i].entry);
			indexCount++;
		}
	}
}

int main() {
	int i;
	FreeSpace fs; // declare freespace
	
	// set all entries in blocks to empty
	for (i=0;i < ((NUM_DATA + NUM_DIR) * NUM_ENTRIES); i++) {
		fs.freeSpaceEntries[i].status = 0; 
	}

	display_block_info(); // display block information
	
	char line[1024];
	char tempLine[1024];
	char separator[] = ",";
	char *token;

	for (i = 0 ; i < 3 ; i++) {
		FILE *fp = fopen("ICT1007-SampleCSV.csv", "r"); // open file pointer

		// while there is still line to be read from fp, loop will continue.
		while (fgets(line, 1024, fp)) {
			strcpy(tempLine,line); // copy content from line to tempLine

			token = strtok(line, separator); // get first token and add token will be add/read/delete
			
			// add based on allocation method
			if (strcmp(token, "add") == 0) {
				
				// index add allocation
				if (i == 0) {
					//addIndex(tempLine);
					//printf("%s", tempLine); // debug; print what is to be added
				}

				// linked add allocation
				if (i == 1) {
					//addLinked(tempLine);
					//printf("%s", tempLine); // debug; print what is to be added
				}

				// contiguous add allocation
				if (i == 2) {
					//addContiguous(tempLine);
					//printf("%s", tempLine); // debug; print what is to be added
				}
			}
			
			// read based on allocation method
			else if (strcmp(token, "read") == 0) {

				// index read allocation
				if (i == 0) {
					//readIndex(tempLine);
					//printf("%s", tempLine); // debug; print what is to be read
				}

				// linked read allocation
				else if (i == 1) {
					//readLinked(tempLine);
					//printf("%s", tempLine); // debug; print what is to be read
				}

				// contiguous read allocation
				else if (i == 2) {
					//readContiguous(tempLine);
					//printf("%s", tempLine); // debug; print what is to be read
				}
			}

			// delete based on allocation method
			else if (strcmp(token, "delete") == 0) {

				// index delete allocation
				if (i == 0) {
					//deleteIndex(tempLine);
					//printf("%s", tempLine); // debug; print what is to be delete
				}

				// linked delete allocation
				else if (i == 1) {
					//deleteLinked(tempLine);
					//printf("%s", tempLine); // debug; print what is to be delete
				}

				// contiguous delete allocation
				else if (i == 2) {
					//deleteContiguous(tempLine);
					//printf("%s", tempLine); // debug; print what is to be delete
				}
			}
		}
	}
}