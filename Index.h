#pragma once

#include <stdbool.h>
#include "freespace.h"

// Method calling
bool addIndex(char *file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);
bool create_file_using_index_method(int file_id, int size, int* content, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);
void readIndex(char* file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);
void deleteIndex(char* file_info, DirectoryNo *dir, DataNo *data, FreeSpaceDirectoryNo *fsDirNo, FreeSpaceDataNo *fsDataNo);
