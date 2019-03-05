#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freespace.h"
#include "Index.h"
#include "contiguous.h"

int main() {
	
	DirectoryNo dir; // create a directory structure
	DataNo data; // create a data structure
	FreeSpaceDirectoryNo fsDirNo; // create free space directory
	FreeSpaceDataNo fsDataNo; // create free space data

	char line[1024];
	char tempLine[1024];
	char separator[] = ",";
	char *token;

	int i;
	for (i = 0 ; i < 3 ; i++) {
		startUp(&dir, &data, &fsDirNo, &fsDataNo);// initialize all block to empty

		//displayBlockInfo(&dir, &data, &fsDirNo, &fsDataNo); // display block information

		FILE *fp = fopen("ICT1007-SampleCSV.csv", "r"); // open file pointer

		// while there is still line to be read from fp, loop will continue.
		while (fgets(line, 1024, fp)) {
			strcpy(tempLine,line); // copy content from line to tempLine

			token = strtok(line, separator); // get first token and add token will be add/read/delete
			
			// add based on allocation method
			if (strcmp(token, "add") == 0) {
				
				// index add allocation
				if (i == 0) {
					// log start timestamp
					addIndex(tempLine, &dir, &data, &fsDirNo, &fsDataNo);
					// log end timestamp
					displayBlockInfo(&dir, &data, &fsDirNo, &fsDataNo); // display block information
				}

				// linked add allocation
				if (i == 1) {
					//addLinked(tempLine);
				}

				// contiguous add allocation
				if (i == 2) {
					addContiguous(tempLine, &dir, &data, &fsDirNo, &fsDataNo);
					//displayBlockInfo(dir, data); // display block information
				}
			}
			
			// read based on allocation method
			else if (strcmp(token, "read") == 0) {
				
				if (i == 0) {
					readIndex(tempLine, &dir, &data, &fsDirNo, &fsDataNo);
					//displayBlockInfo(dir, data); // display block information
				}

				else if (i == 1) {
					//readLinked(tempLine);
				}

				else if (i == 2) {
					//readContiguous(tempLine);
				}
			}

			// delete based on allocation method
			else if (strcmp(token, "delete") == 0) {

				// index delete allocation
				if (i == 0) {
					deleteIndex(tempLine, &dir, &data, &fsDirNo, &fsDataNo);
					//displayBlockInfo(dir, data); // display block information
				}

				// linked delete allocation
				else if (i == 1) {
					//deleteLinked(tempLine);
				}

				// contiguous delete allocation
				else if (i == 2) {
					//deleteContiguous(tempLine);
				}
			}
		}
	}
}

/*
debug; printf lines
======================================================
//printf("%s", tempLine);
======================================================

debug; check available block(s) in main
======================================================
	displayBlockInfo(dir, data); // display block information
	
	int x = freeSpaceCheck(fsDataNo);
	printf("%d",x); 

	int y = contiguousCheck(5, fsDataNo);
	printf("%d",y); 
	
	int z = directoryCheck(dir,fsDirNo);
	printf("%d\n", z);
======================================================
*/