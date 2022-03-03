#include <stdlib.h>
#include "random-pairs.h"

struct random_pairs *random_pairs_new(int object_num, int pair_num) {
    if (object_num < 2 || pair_num < 0) return NULL;

    int (*pairs)[2] = malloc(sizeof(pairs) * pair_num);
    if (pairs == NULL) return NULL;
    
    for (int i = 0; i < pair_num; i++) {
		pairs[i][0] = rand() % object_num;
		do {
			pairs[i][1] = rand() % object_num;
		} while (pairs[i][1] == pairs[i][0]);
	}

    struct random_pairs *res = malloc(sizeof(*res));
    if (res == NULL) return NULL;
    
    res->pairs = pairs;

    return res;
}

void random_pairs_delete(struct random_pairs *pairs) {
    if (pairs != NULL) {
        free(pairs->pairs);
        free(pairs);
    }

    return;
}
