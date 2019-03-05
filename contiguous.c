#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "freespace.h"
#include "contiguous.h"

void addContiguous(char *tempLine, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo){
    
    int directoryCounter = -1;
    int i,j;

    /* LOOP THROUGH EACH DIRECTORY BLOCK*/
    for (i = 0; i < NUM_DIR; i++){
        /* LOOP THROUGH ENTRIES IN THE BLOCK */
        for (j = 0; j < NUM_ENTRIES; j++) {
            if(dir->directory[i].directoryEntries[j].fileID == -1) {
                directoryCounter = j;
                break;
            }
        }
    }
    
    if (directoryCounter == -1) {
        printf("Directory Block no longer have space for input.\n");
    }
    else {
        const char separator[] = ", ";
        char *token;


        token = strtok(NULL, separator);
        dir->directory[0].directoryEntries[directoryCounter].fileID = atoi(token); // assign fileID to directory
        fsDirNo->freeSpaceDirectory[0].freeSpaceDirectoryEntries[directoryCounter].status = 1;

        int file_size = 0;
        int content[1024];
        token = strtok(NULL, separator);
        while (token != NULL) {
            content[file_size] = atoi(token);
            file_size++;
            token = strtok(NULL, separator);
        }
        int numBlocks = ceil((double)file_size/NUM_ENTRIES); // get ceiling to know number of blocks needed
        int startBlock = contiguousCheck (numBlocks, fsDataNo);
        printf("STARTING BLOCK :     %d\n", startBlock);

        dir->directory[0].directoryEntries[directoryCounter].start = startBlock;
        
        int endBlock = startBlock + numBlocks - 1;
        dir->directory[0].directoryEntries[directoryCounter].end = endBlock;

        j = 0;
        for (i = 0; i < file_size; i++){
            data->data[startBlock + i/4].dataEntries[i%4].entry = content[i];
        }

        displayBlockInfo(dir, data, fsDirNo, fsDataNo);
    }
    /*
    int numBlocks = ceil(i/NUM_ENTRIES); // get ceiling to know number of blocks needed
    int startBlock = contiguousCheck(numBlocks, fsDataNo);
    int endBlock = startBlock + numBlocks -1;
    //printf("Start: %d | End:%d\n",startBlock, endBlock);
    
    /*
    dir->directoryEntries[0].fileID = atoi(storage[0]); // assign fileID to directory
    dir->directoryEntries[0].start = startBlock;
    dir->directoryEntries[0].end = endBlock;
    fsDirNo->freeSpaceDirectory[0].status = 1;

    for (; startBlock <= endBlock; startBlock++){
        fsDataNo->freeSpaceData[startBlock].status = 1;
    }
    */

    /*
    fsDirNo->freeSpaceDirectory[contiguousCount].status = 1;
    for (; startBlock <= endBlock; startBlock++){
        fsDataNo->freeSpaceData[startBlock].status = 1;
        for(i=0;i<NUM_ENTRIES;i++){
            data->dataEntries[i].entry = atoi(storage[i+2]);
        }
    }
    */
    
    //displayBlockInfo(dir, data, fsDirNo, fsDataNo);
}