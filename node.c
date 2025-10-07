#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "node.h"

node_t create_dummy_node(void) {
	node_t ret = {
		.value	= INT_MIN,
		.next	= NULL,
	};

	return ret;
}

node_t create_node(const int value) {
	node_t ret = {
		.value	= value,
		.next	= NULL,
	};

	return ret;
}

node_t *create_node_with_next(const int value, node_t *next) {
	node_t *ret = malloc(sizeof(node_t));
	if (ret == NULL) {
		fprintf(stderr, "failed to allocate node memory!\n");
		fprintf(stderr, "[ret]: value = %d, next = %p\n", value, next);
		return NULL;
	}

	ret->value = value;
	ret->next = next;
	return ret;
}

void free_node(node_t *node) {
	if (node == NULL) {
		fprintf(stderr, "cannot free a null node!\n");
		return;
	}

	free(node);
}
