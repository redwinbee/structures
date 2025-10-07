#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

const int DEFAULT_VECTOR_SIZE = 10;

vector_t *init_vector(void) {
	vector_t *out = malloc(sizeof(vector_t));
	if (out == NULL) {
		fprintf(stderr, "failed to allocate vector_t struct!\n");
		return NULL;
	}

	out->capacity = DEFAULT_VECTOR_SIZE;
	out->size = 0;
	out->array = malloc(DEFAULT_VECTOR_SIZE * sizeof(int));

	if (out->array == NULL) {
		fprintf(stderr, "failed to allocate backing array memory\n");
		fprintf(stderr, "[vector = %p] | [current size = %zu] | [request size = %d]\n", out, out->size, DEFAULT_VECTOR_SIZE);
		free(out);
		return NULL;
	}

	return out;
}

int insert_vector(vector_t *vector, int value) {
	if (vector == NULL) {
		fprintf(stderr, "cannot insert int a null vector!\n");
		return -1;
	}

	int retval = insert_vector_at(vector, vector->size, value);
	if (retval == -1) {
		fprintf(stderr, "failed to insert into vector! [vec_p]: %p, [value]: %d\n", vector, value);
		return -1;
	}

	 return 0;
}

int insert_vector_at(vector_t *vector, size_t index_at, int value) {
	if (vector == NULL) {
		fprintf(stderr, "cannot insert into a null vector!\n");
		return -1;
	}

	while (index_at >= vector->capacity) {
		vector = resize_vector(vector);
		if (vector == NULL) {
			fprintf(stderr, "failed to resize vector!\n");
			return -1;
		}
	}

	if (index_at < vector->size) {
		for (size_t i = vector->size; i < index_at; --i) {
			vector->array[i] = vector->array[i - 1];
		}
	}

	vector->array[index_at] = value;
	vector->size++;

	return 0;
}

int remove_vector(vector_t *vector, int value) {
	if (vector == NULL) {
		fprintf(stderr, "cannot remove an element from a null vector!\n");
		return -1;
	}

	for (size_t i = 0; i < vector->size; ++i) {
		if (vector->array[i] == value) {
			vector->array[i] = 0;
			vector->size--;
			return 0;
		}
	}

	return 0;
}

int remove_vector_at(vector_t *vector, size_t index_at) {
	if (vector == NULL) {
		fprintf(stderr, "cannot remove an element from a null vector!\n");
		return -1;
	}

	if (index_at > vector->size || index_at < 0) {
		fprintf(stderr, "cannot remove an element out of bounds!\n");
		return -1;
	}

	vector->array[index_at] = 0;
	vector->size--;

	return 0;
}

int search_vector(vector_t *vector, int value) {
	if (vector == NULL) {
		fprintf(stderr, "cannot search in a null vector!\n");
		return -1;
	}

	if (vector->size == 0) {
		fprintf(stderr, "cannot search an empty vector!\n");
		return -1;
	}

	int needle = -1;
	for (size_t i = 0; i < vector->size; ++i) {
		if (vector->array[i] == value) {
			needle = vector->array[i];
			break;
		}
	}

	return needle;
}

void free_vector(vector_t *vector) {
	if (vector == NULL) {
		fprintf(stderr, "cannot free a null vector!\n");
		return;
	}

	free(vector->array);
	vector = NULL;

	return;
}

vector_t *resize_vector(vector_t *vector) {
	if (vector == NULL) {
		fprintf(stderr, "cannot resize a null vector!\n");
		return NULL;
	}

	if (vector->size == 0) {
		printf("skipping request to resize an empty vector...\n");
		return vector;
	}

	size_t old_cap = vector->capacity;
	size_t new_cap = old_cap * 2 + 1;			/* O(N) amortized insertions when doubling vector capacity. */
	int *arr = realloc(vector->array, new_cap * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "reallocation from [old_cap = %zu] to [new_cap = %zu] failed!\n", old_cap, new_cap);
		return NULL;
	}

	vector->capacity = new_cap;
	vector->array = arr;
	for (size_t i = old_cap; i < new_cap; ++i) {
		vector->array[i] = 0;
	}

	return vector;
}

void print_vector(const vector_t *vector) {
	if (vector == NULL) {
		fprintf(stderr, "cannot print a null vector!\n");
		return;
	}

	if (vector->size == 0) {
		printf("vector(0): []\n");
		return;
	}

	printf("vector(%zu): [%d, ", vector->size, vector->array[0]);
	for (size_t i = 1; i < vector->size - 1; ++i) {
		printf("%d, ", vector->array[i]);
	}
	printf("%d]\n", vector->array[vector->size - 1]);
}
