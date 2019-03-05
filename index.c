#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "index.h"
#include "freespace.h"

bool addIndex(char *file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo) {
	char separator[] = ", ";
	char *token;
	char line[1024];

	strcpy(line, file_info); // copy content from line to tempLine

	token = strtok(line, separator); // get first token and add token will be add/read/delete
	token = strtok(NULL, separator);

	int file_id = atoi(token);
	int file_size = 0;
	int content[1024];
	token = strtok(NULL, separator);

	while (token != NULL) {
		content[file_size] = atoi(token);
		file_size++;
		token = strtok(NULL, separator);
	}
	
	bool succeed = create_file_using_index_method(file_id, file_size, content, dir, data, fsDirNo, fsDataNo);

	return succeed;
}

bool create_file_using_index_method(int file_id, int size, int* content, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo) {

	int num_blocks = ceil((double)size/NUM_ENTRIES);	
	int available_directory_entry;
	int index_block;
	int available_next_block;
	
	available_directory_entry = directoryCheck(fsDirNo);
	fsDirNo->freeSpaceDirectory[0].freeSpaceDirectoryEntries[available_directory_entry].status = 1;
	dir->directory[0].directoryEntries[available_directory_entry].fileID = file_id;

	index_block = freeSpaceCheck(fsDataNo); 
	dir->directory[0].directoryEntries[available_directory_entry].start = index_block + 1;
	dir->directory[0].directoryEntries[available_directory_entry].end = index_block + 1 + num_blocks;
	
	int i, j, k = 0;
	for (i = 0; i < num_blocks;i++) {
		fsDataNo->freeSpaceData[index_block].freeSpaceDataEntries[i].status = 1;
		
		int available_next_block = freeSpaceCheck(fsDataNo);
		data->data[index_block].dataEntries[i].entry = available_next_block + 1;
		
		for (k, j = 0; k < size && j < NUM_ENTRIES; k++, j++) {
			data->data[available_next_block].dataEntries[j].entry = content[k];
			fsDataNo->freeSpaceData[available_next_block].freeSpaceDataEntries[j].status = 1;
		}
		printf("\nDir: %d | Index: %d | Avail: %d\n",available_directory_entry, index_block, available_next_block);
	}
	
	if ((num_blocks > 4) || (available_directory_entry == -1) || (index_block == -1)) {
		return false;
	}
	return true; // all succeed!
}

void readIndex(char* file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo)
{
	char separator[] = ", ";
	char *token;
	char line[1024];

	strcpy(line, file_info); // copy content from line to tempLine

	token = strtok(line, separator); // get first token and add token will be add/read/delete
	token = strtok(NULL, separator);
	int data_to_read = atoi(token);
	
	int i, j;
	bool bFound = false;
	
	for (i = 0; i < NUM_DATA; i++) {
		for (j = 0; j < NUM_ENTRIES; j++) {
			if (data->data[i].dataEntries[j].entry == data_to_read) {
				bFound = true;
				break;
			}
		}
		if (bFound){
			break;
		}
	}

	if(bFound) {
		printf("Read file%d(%d) from B%d(a%d), B%d(a%d,a%d)\n", i, data_to_read, i, i, i, i, i);
	}
	else {
		//printf("%s FAILED!", file_info);
	}
	return;
}

void deleteIndex(char* file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo)
{
	char separator[] = ", ";
	char *token;
	char line[1024];

	strcpy(line, file_info); // copy content from line to tempLine

	token = strtok(line, separator); // get first token and add token will be add/read/delete
	token = strtok(NULL, separator);
	int file_id = atoi(token);

	// search for file id in directory entry
	int directory_entry = -1;
	bool bFound = false;
	int i, j;
	for(i = 0; i < NUM_DIR; i++){
		for(j = 0; j < NUM_ENTRIES; j++) {
			if (dir->directory[i].directoryEntries[j].fileID == file_id) {
				bFound = true;
				directory_entry = j;
				break;
			}
		}
	}	

	if (bFound)	{
		for(i = 0; i < NUM_DIR;i++){
			int start_block_index = dir->directory[i].directoryEntries[directory_entry].start;
			int end_block_index = dir->directory[i].directoryEntries[directory_entry].end;
			for (i = start_block_index; i <= end_block_index; i++) {
				for (j = 0; j < NUM_ENTRIES; j++){
					data->data[i - 1].dataEntries[j].entry = -1; // reset to -1
				}
			}
		}
		
		// clear file id in directory entry
		for (i = 0; i < NUM_DIR; i++){
			dir->directory[i].directoryEntries[directory_entry].fileID = -1;
			dir->directory[i].directoryEntries[directory_entry].start = -1;
			dir->directory[i].directoryEntries[directory_entry].end = -1;
		}
	}

	//int block_index = 0;
	//int entry_index = 0;
	//bool bFound = false;
	//for (block_index = 0; block_index < NUM_DATA;block_index++)
	//{
	//	for (entry_index = 0; entry_index < NUM_ENTRIES; entry_index++)
	//	{
	//		if (data->data[block_index].dataEntries[entry_index].entry == data_to_read)
	//		{
	//			bFound = true;
	//			break;
	//		}
	//	}

	//	if (bFound)
	//		break;
	//}

	//if (bFound)
	//	printf("%s SUCCEEDED! Block %d, entry %d", file_info, block_index + 1, entry_index + 1);
	//else
	//	printf("%s FAILED!", file_info);


	return;
}