#pragma once

#include <stddef.h>

typedef struct vector {
	size_t capacity;
	size_t size;
	int *array;
} vector_t;

vector_t *init_vector(void);
int insert_vector(vector_t *vector, int value);
int insert_vector_at(vector_t *vector, size_t index_at, int value);
int remove_vector(vector_t *vector, int value);
int remove_vector_at(vector_t *vector, size_t index_at);
int search_vector(vector_t *vector, int value);
void free_vector(vector_t *vector);
vector_t *resize_vector(vector_t *vector);
void print_vector(const vector_t *vector);
