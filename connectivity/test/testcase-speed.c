#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connectivity.h"
#include "random-pairs.h"
#include "time-utils.h"
#include "testcase-speed.h"

static int g_object_num = 0;
static int g_pair_num = 0;
static struct random_pairs *g_input_pairs = NULL;
static const char *g_scale = NULL;

void random_input_setup(int object_num, int pair_num, const char *scale) {
    g_object_num = object_num;
    g_pair_num = pair_num;
    g_input_pairs = random_pairs_new(g_object_num, g_pair_num);
    g_scale = scale;
    if (g_input_pairs == NULL) ck_abort_msg("fail to generate random pairs.\n");
    printf("\n======speed test in %s amount starts======\n", g_scale);
}

void random_input_setup_tiny_amount(void) {
    random_input_setup(1e3, 5e3, "tiny");
}

void random_input_setup_small_amount(void) {
    random_input_setup(1e4, 5e4, "small");
}

void random_input_setup_medium_amount(void) {
    random_input_setup(1e5, 5e5, "medium");
}

void random_input_setup_large_amount(void) {
    random_input_setup(1e6, 5e6, "large");
}

void random_input_setup_massive_amount(void) {
    random_input_setup(1e7, 5e7, "massive");
}

void random_input_teardown(void) {
    if (g_input_pairs != NULL) random_pairs_delete(g_input_pairs);
    printf("======speed test in %s amount ends======\n", g_scale);
}

void print_used_time(const char *algorithm, clock_t start_time, clock_t end_time) {
    double cpu_time_used = compute_used_cpu_time(start_time, end_time);
	printf("%s took %f seconds to process %d(%.1e) connections in %d(%.1e) objects.\n", algorithm, cpu_time_used,  g_pair_num,  (double)g_pair_num, g_object_num, (double)g_object_num);
}

START_TEST(speed_test_qfind) {
    int *storage = qfind_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        qfind_is_new_connection(storage, g_object_num, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("quick find", start_time, end_time);

    qfind_delete_storage(storage);
} END_TEST

START_TEST(speed_test_qunion) {
    int *storage = qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        qunion_is_new_connection(storage, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("quick union", start_time, end_time);

    qunion_delete_storage(storage);
} END_TEST

START_TEST(speed_test_w_qunion) {
    struct storage_with_tree_size *storage = w_qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        w_qunion_is_new_connection(storage, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("weighted quick union", start_time, end_time);

    w_qunion_delete_storage(storage);
} END_TEST

START_TEST(speed_test_w_qunion_pc) {
    struct storage_with_tree_size *storage = w_qunion_pc_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        w_qunion_pc_is_new_connection(storage, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("weighted quick union with path compression", start_time, end_time);

    w_qunion_pc_delete_storage(storage);
} END_TEST

START_TEST(speed_test_w_qunion_pc_h) {
    struct storage_with_tree_size *storage = w_qunion_pc_h_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        w_qunion_pc_h_is_new_connection(storage, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("weighted quick union with path compression by halving", start_time, end_time);

    w_qunion_pc_h_delete_storage(storage);
} END_TEST

START_TEST(speed_test_h_qunion) {
    struct storage_with_tree_height *storage = h_qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);

    clock_t start_time = clock();

    for (int i = 0; i < g_pair_num; i++) {
        h_qunion_is_new_connection(storage, g_input_pairs->pairs[i][0], g_input_pairs->pairs[i][1]);
    }

    clock_t end_time = clock();

    print_used_time("heighted quick union", start_time, end_time);

    h_qunion_delete_storage(storage);
} END_TEST

void suite_add_testcase_speed(Suite *s) {

#define TC_SPEED(scale, timeout) \
do { \
    TCase *tc_speed_##scale = tcase_create("Speed Testcase - " #scale " amount"); \
    tcase_set_timeout(tc_speed_##scale, (timeout)); \
    tcase_add_unchecked_fixture(tc_speed_##scale, random_input_setup_##scale##_amount, random_input_teardown); \
    tcase_add_test(tc_speed_##scale, speed_test_qfind); \
    tcase_add_test(tc_speed_##scale, speed_test_qunion); \
    tcase_add_test(tc_speed_##scale, speed_test_w_qunion); \
    tcase_add_test(tc_speed_##scale, speed_test_w_qunion_pc); \
    tcase_add_test(tc_speed_##scale, speed_test_w_qunion_pc_h); \
    tcase_add_test(tc_speed_##scale, speed_test_h_qunion); \
    suite_add_tcase(s, tc_speed_##scale); \
} while (0);

    TC_SPEED(tiny, 10);
    TC_SPEED(small, 10);
    TC_SPEED(medium, 10);
    TC_SPEED(large, 10);
    TC_SPEED(massive, 10);

#undef TC_SPEED

    return;
}
