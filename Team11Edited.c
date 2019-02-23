#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_DIR 1 // define number of directory block
#define NUM_DATA 31 // define number of data block
#define NUM_ENTRIES 4 // define entries in a block

// Directory Entries
typedef struct directoryEntries {
	int index;
	int blockNo;
	int fileID;
	int start;
	int end;
} DirectoryEntries;

// Directory
typedef struct directory {
	DirectoryEntries directoryEntries[NUM_ENTRIES];
} Directory;

// Number of Directory blocks
typedef struct directoryNo {
	Directory directory[NUM_DIR];
} DirectoryNo;

// Data Entries
typedef struct dataEntries{
	int index; 
	int blockNo;
	int entry;
	int status; // 1: allocated, 0: otherwise (means is empty)
	int jump;
} DataEntries;

// Data
typedef struct data {
	DataEntries dataEntries[NUM_ENTRIES];
} Data;

// Number of Data blocks
typedef struct dataNo {
	Data data[NUM_DATA];
} DataNo;

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

	
	for (blockCount; blockCount <= NUM_DATA; blockCount++) {
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
	
	char line[1024];
	FILE *fp = fopen("ICT1007-SampleCSV.csv", "r"); // open file pointer
	
	/*
	while (fgets(line, 1024, fp)) {
		printf(line);
	}
	*/
	
	// display block informtion
	display_block_info();

	// read the file content
	// add, 100, 101, 102, 103, 104, 105, 106 ---> token will be add then 100 then 101 ...
	// add, 200, 201, 202, 203
	// read, 106
	// delete, 200
	// we need to use string tokenizer to read comma-separated text

	/*
		char separator[2] = ",";
		char * token;

		// get the first token
		// token will be add
		token = strtok(line, separator); // token will be add/read/delete
		bool addNewFile = false;

		// for reading "add" = creating new file to start storing.
		if (strcmp(token, "add") == 0)  // we need to create a new file, "add" - "add" == 0, "read" - "add" will not be 0
		{
			total_files++;

			addNewFile = true;

			// initialize file info
			files[total_files - 1].id = -1;
			files[total_files - 1].size = 0;
		}

		total_file_operations++; // add new file operation (Add/Read/Delete)
		if (strcmp(token, "add") == 0)
		{
			file_operations[total_file_operations - 1].type = Add;
		}
		else if (strcmp(token, "read") == 0)
		{
			file_operations[total_file_operations - 1].type = Read;
		}
		else if (strcmp(token, "delete") == 0)
		{
			file_operations[total_file_operations - 1].type = Delete;
		}

		// walk through other tokens
		while (token != NULL)
		{
			printf("%s \n", token);



			// this is to read next token, token will be 100 and s will be 101, 102, ...
			// btw, file identifiers : 100, 200, 300 etc
			// file contents : 101, 102, 201, 202 .. etc
			token = strtok(NULL, separator);

			if (token == NULL)
				break;
			if (file_operations[total_file_operations - 1].type == Add)
			{
				if (files[total_files - 1].id == -1)
				{
					// for adding file
					file_operations[total_file_operations - 1].file_id = files[total_files - 1].id = atoi(token); //atoi function is to change strings to int
				}
				else
				{
					files[total_files - 1].content[files[total_files - 1].size] = atoi(token);
					files[total_files - 1].size++;
				}
			}
			else if(file_operations[total_file_operations - 1].type == Read)
			{
				file_operations[total_file_operations-1].entry_to_read = atoi(token);
			}
			else if (file_operations[total_file_operations - 1].type == Delete)
			{
				file_operations[total_file_operations - 1].file_id = atoi(token);
			}
		}
	}
	*/

	fclose(fp); // finish reading the file

	/*
	// Go through the list of file operatioins
	for (int i = 0; i < total_file_operations; i++)
	{
		if (file_operations[i].type == Add) // we need to add a new file
		{
			// Get the file Id
			int file_id = file_operations[i].file_id;// file is 100
			for (int j = 0; j < total_files;j++) // look for the file 
			{
				if (files[j].id == file_operations[i].file_id) // found the file which matches the file id
				{
					allocate_disk_block_using_index_method(files[j]);

					// allocate_disk_block_using_contigous_method(files[j]);

					// allocae_disk_block_using_linked_list_method(files[j]);
					break;
				}
			}
		}
		else if (file_operations[i].type == Read)
		{

		}
		else if (file_operations[i].type == Delete)
		{

		}
	}
	*/
}