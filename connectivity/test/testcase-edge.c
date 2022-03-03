#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "connectivity.h"
#include "time-utils.h"
#include "testcase-edge.h"

static void edge_test(int object_num) {
    printf("\n======edge test with %d objects starts======\n", object_num);

    struct storage_with_tree_size *storage = w_qunion_pc_h_new_storage(object_num);
    ck_assert_ptr_nonnull(storage);

    int pair[2] = {0};
    unsigned long long edge_count = 0;

    clock_t start_time = clock();

    int i = 0;
    while (i < object_num - 1) {
        pair[0] = rand() % object_num;
		do {
			pair[1] = rand() % object_num;
		} while (pair[1] == pair[0]);

        if (w_qunion_pc_h_is_new_connection(storage, pair[0], pair[1])) {
            i++;
        }

        edge_count++;
        if (edge_count == ULLONG_MAX) {
            ck_abort_msg("so much edges has been generated that even unsigned long long cannot hold their count\n");
        }
    }

    clock_t end_time = clock();

    double cpu_time_used = compute_used_cpu_time(start_time, end_time);

    printf("it takes %lld random edges to connect %d objects.\n%f seconds has elapsed.\n", edge_count, object_num, cpu_time_used);

    w_qunion_pc_h_delete_storage(storage);

    printf("======edge test with %d objects ends======\n", object_num);
}

START_TEST(edge_test_tiny_amount) {
    edge_test(1e3);
} END_TEST

START_TEST(edge_test_small_amount) {
    edge_test(1e4);
} END_TEST

START_TEST(edge_test_medium_amount) {
    edge_test(1e5);
} END_TEST

START_TEST(edge_test_large_amount) {
    edge_test(1e6);
} END_TEST

START_TEST(edge_test_massive_amount) {
    edge_test(1e7);
} END_TEST

void suite_add_test_case_edge(Suite *s) {
    TCase *tc_edge = tcase_create("Edge Testcase");
    tcase_set_timeout(tc_edge, 30);
    tcase_add_test(tc_edge, edge_test_tiny_amount);
    tcase_add_test(tc_edge, edge_test_small_amount);
    tcase_add_test(tc_edge, edge_test_medium_amount);
    tcase_add_test(tc_edge, edge_test_large_amount);
    tcase_add_test(tc_edge, edge_test_massive_amount);
    suite_add_tcase(s, tc_edge);
    return;
}
