#include <stdio.h>
#include "vector.h"

int main(int argc, char **argv) {
	vector_t *p_vec = init_vector();
	if (!p_vec) {
		fprintf(stderr, "no vector!\n");
		return -1;
	}

	int count = 0;
	for (int i = 0; i < 100; ++i) {
		insert_vector_at(p_vec, i, count++);
	}

	print_vector(p_vec);

	return 0;
}
