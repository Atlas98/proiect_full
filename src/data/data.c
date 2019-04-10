#include <internal.h>
#include "data.h"
#include <stdlib.h>
#include <stdio.h>

//static struct data database[7];

EXPORT_FUNCTION struct data* get_data_struct(int k) {
	struct data* data_ptr = data_create();
	data_ptr->k = k;
	return data_ptr;
}

/* UNIMPLEMENTED
EXPORT_FUNCTION int check_integrity(struct data* db, int chapter) {
    return 0;
}
*/

EXPORT_FUNCTION int data_save_to_file(struct data* data, char* filename) {
	FILE* filePtr = fopen(filename, "w+");
	if (filePtr == NULL) {
		printf("File pointer is null!\n");
		return 0;
	}
	fwrite(data, sizeof(struct data), 1, filePtr);
	fclose(filePtr);
	printf("Wrote data to file!\n");
	return 1;
}

EXPORT_FUNCTION struct data* data_load_from_file(char* filename) {
	FILE* filePtr = fopen(filename, "r");
	if (filePtr == NULL) {
		printf("File pointer is null!\n");
		return NULL;
	}
	struct data* dataPtr = malloc(sizeof(struct data));
	fclose(filePtr);
	printf("Got data from file!\n");
	return dataPtr;
}
EXPORT_FUNCTION struct data* data_create() {
	struct data* data_ptr = (struct data*) malloc(sizeof(struct data));
	return data_ptr;
}
EXPORT_FUNCTION void data_free(struct data* data) {
	free(data);
}

/*
EXPORT_FUNCTION void data_load_to_database(struct data* dataPtr, int k) {
	database[k] = *dataPtr;
	data_free(dataPtr);
}
*/
