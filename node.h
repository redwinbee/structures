#pragma once

typedef struct node {
	int value;
	struct node *next;
} node_t;

node_t create_dummy_node(void);
node_t create_node(const int value);
node_t *create_node_with_next(const int value, node_t *next);
void free_node(node_t *nod);

