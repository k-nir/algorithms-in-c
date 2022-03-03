#include <stdlib.h>
#include "connectivity.h"
#include "testcase-correctness.h"

// 正确性测试用例中对象的个数
static const int g_object_num = 10;

// 代表新连接的输入对
static int g_new_connection_pairs[][2] = {
    {3, 4},
    {4, 9},
    {8, 0},
    {2, 3},
    {5, 6},
    {5, 9},
    {7, 3},
    {4, 8},
    {6, 1}
};

// 代表旧连接的输入对
static int g_old_connection_pairs[][2] = {
    {2, 9},
    {5, 6},
    {0, 2}
};

// 测试Quick-find算法的正确性
START_TEST(correctness_test_qfind) {
    int *storage = qfind_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Quick-find算法应将所有输入对判断为新连接
        ck_assert(qfind_is_new_connection(storage, g_object_num, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Quick-find算法应将所有输入对判断为旧连接
        ck_assert(!qfind_is_new_connection(storage, g_object_num, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    qfind_delete_storage(storage);
} END_TEST

// 测试Quick-union算法的正确性
START_TEST(correctness_test_qunion) {
    int *storage = qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Quick-union算法应将所有输入对判断为新连接
        ck_assert(qunion_is_new_connection(storage, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Quick-union算法应将所有输入对判断为旧连接
        ck_assert(!qunion_is_new_connection(storage, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    qunion_delete_storage(storage);
} END_TEST

// 测试Weighted-quick-union算法的正确性
START_TEST(correctness_test_w_qunion) {
    struct storage_with_tree_size *storage = w_qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为新连接
        ck_assert(w_qunion_is_new_connection(storage, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为旧连接
        ck_assert(!w_qunion_is_new_connection(storage, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    w_qunion_delete_storage(storage);
} END_TEST

// 测试Weighted-quick-union-with-path-compression算法的正确性
START_TEST(correctness_test_w_qunion_pc) {
    struct storage_with_tree_size *storage = w_qunion_pc_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为新连接
        ck_assert(w_qunion_pc_is_new_connection(storage, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为旧连接
        ck_assert(!w_qunion_pc_is_new_connection(storage, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    w_qunion_pc_delete_storage(storage);
} END_TEST

// 测试Weighted-quick-union-with-path-compression-by-halving算法的正确性
START_TEST(correctness_test_w_qunion_pc_h) {
    struct storage_with_tree_size *storage = w_qunion_pc_h_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为新连接
        ck_assert(w_qunion_pc_h_is_new_connection(storage, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Weighted-quick-union算法应将所有输入对判断为旧连接
        ck_assert(!w_qunion_pc_h_is_new_connection(storage, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    w_qunion_pc_h_delete_storage(storage);
} END_TEST

// 测试Heighted-quick-union算法的正确性
START_TEST(correctness_test_h_qunion) {
    struct storage_with_tree_height *storage = h_qunion_new_storage(g_object_num);
    ck_assert_ptr_nonnull(storage);
    // 输入代表新连接的输入对
    for (int i = 0; i < sizeof(g_new_connection_pairs)/sizeof(g_new_connection_pairs[0]); i++) {
        // 此处Heighted-quick-union算法应将所有输入对判断为新连接
        ck_assert(h_qunion_is_new_connection(storage, g_new_connection_pairs[i][0], g_new_connection_pairs[i][1]));
    }
    // 输入代表旧连接的输入对
    for (int i = 0; i < sizeof(g_old_connection_pairs)/sizeof(g_old_connection_pairs[0]); i++) {
        // 此处Heighted-quick-union算法应将所有输入对判断为旧连接
        ck_assert(!h_qunion_is_new_connection(storage, g_old_connection_pairs[i][0], g_old_connection_pairs[i][1]));
    }
    
    h_qunion_delete_storage(storage);
} END_TEST

void suite_add_testcase_correctness(Suite *s) {
    TCase *tc_correct = tcase_create("Correctness Testcase");
    tcase_add_test(tc_correct, correctness_test_qfind);
    tcase_add_test(tc_correct, correctness_test_qunion);
    tcase_add_test(tc_correct, correctness_test_w_qunion);
    tcase_add_test(tc_correct, correctness_test_w_qunion_pc);
    tcase_add_test(tc_correct, correctness_test_w_qunion_pc_h);
    tcase_add_test(tc_correct, correctness_test_h_qunion);
    suite_add_tcase(s, tc_correct);
    return;
}
