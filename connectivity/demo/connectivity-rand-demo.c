#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "sytnax: %s object_num pair_num\n", argv[0]);
		exit(-1);
	}

	char *str_end = NULL;
	bool range_err;
	
	errno = 0;
	long input_num_1 = strtol(argv[1], &str_end, 0);
	range_err = errno == ERANGE;
	if (str_end[0] != '\0') {
		fprintf(stderr, "invalid object_num value.\n");
		exit(-1);
	}
	if (range_err || input_num_1 < 2 || input_num_1 > INT_MAX) {
		fprintf(stderr, "object_num out of range.\n");
		exit(-1);
	}


	errno = 0;
	long input_num_2 = strtol(argv[2], &str_end, 0);
	range_err = errno == ERANGE;
	if (str_end[0] != '\0') {
		fprintf(stderr, "invalid pair_num value.\n");
		exit(-1);
	}
	if (range_err || input_num_2 < 0 || input_num_2 > INT_MAX) {
		fprintf(stderr, "pair_num out of range.\n");
		exit(-1);
	}
	
	int object_num = (int)input_num_1;
	int pair_num = (int)input_num_2;
	int (*pairs)[2] = malloc(sizeof(pairs) * pair_num);
	
	clock_t start_time = clock();
	
	for (int i = 0; i < pair_num; i++) {
		pairs[i][0] = rand() % object_num;
		do {
			pairs[i][1] = rand() % object_num;
		} while (pairs[i][1] == pairs[i][0]);
	}

	clock_t end_time = clock();
	
	double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	
	printf("pair generation took %f seconds to complete.\n", cpu_time_used);
	
	free(pairs);
	return 0;
}
