#include <stdlib.h>
#include <check.h>
#include "connectivity.h"
#include "testcase-correctness.h"
#include "testcase-speed.h"
#include "testcase-edge.h"

Suite *connectivity_suite(void) {
    Suite *s = suite_create("Connectivity Suite");    
    suite_add_testcase_correctness(s);
    suite_add_testcase_speed(s);
    suite_add_test_case_edge(s);
    return s;
}

int main() {
    Suite *s = connectivity_suite();
    SRunner *sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * 本测试在debian虚拟机上的运行结果如下列输出所示，
 * 其中，
 *     Quick-find算法和Quick-union算法在speed测试的large和massive规模下耗时太长，
 *     超过timeout，因此没有输出。
 * 
 * 从实际测试来看，带有减半路径压缩的Weighted-Quick-union的性能最好，
 * Heighted-quick-union算法的效率和Weighted-quick-union相差无几。
 * 
 * 从edge测试的结果可知，要将N个对象全部连接到一起(即产生N-1个新连接)，
 * 大约需要loge(X)/2(loge指以e为底数的log)个随机输入对。
 */

/*
======speed test in tiny amount starts======
quick find took 0.002435 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
quick union took 0.004540 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
weighted quick union took 0.000180 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
weighted quick union with path compression took 0.000123 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
weighted quick union with path compression by halving took 0.000096 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
heighted quick union took 0.000190 seconds to process 5000(5.0e+03) connections in 1000(1.0e+03) objects.
======speed test in tiny amount ends======

======speed test in small amount starts======
quick find took 0.228607 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
quick union took 0.379664 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
weighted quick union took 0.001679 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
weighted quick union with path compression took 0.001107 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
weighted quick union with path compression by halving took 0.000859 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
heighted quick union took 0.001697 seconds to process 50000(5.0e+04) connections in 10000(1.0e+04) objects.
======speed test in small amount ends======

======speed test in medium amount starts======
weighted quick union took 0.019847 seconds to process 500000(5.0e+05) connections in 100000(1.0e+05) objects.
weighted quick union with path compression took 0.013449 seconds to process 500000(5.0e+05) connections in 100000(1.0e+05) objects.
weighted quick union with path compression by halving took 0.010489 seconds to process 500000(5.0e+05) connections in 100000(1.0e+05) objects.
heighted quick union took 0.020615 seconds to process 500000(5.0e+05) connections in 100000(1.0e+05) objects.
======speed test in medium amount ends======

======speed test in large amount starts======
weighted quick union took 0.233773 seconds to process 5000000(5.0e+06) connections in 1000000(1.0e+06) objects.
weighted quick union with path compression took 0.148229 seconds to process 5000000(5.0e+06) connections in 1000000(1.0e+06) objects.
weighted quick union with path compression by halving took 0.113970 seconds to process 5000000(5.0e+06) connections in 1000000(1.0e+06) objects.
heighted quick union took 0.242324 seconds to process 5000000(5.0e+06) connections in 1000000(1.0e+06) objects.
======speed test in large amount ends======

======speed test in massive amount starts======
weighted quick union took 6.361550 seconds to process 50000000(5.0e+07) connections in 10000000(1.0e+07) objects.
weighted quick union with path compression took 5.004542 seconds to process 50000000(5.0e+07) connections in 10000000(1.0e+07) objects.
weighted quick union with path compression by halving took 3.878076 seconds to process 50000000(5.0e+07) connections in 10000000(1.0e+07) objects.
heighted quick union took 6.639887 seconds to process 50000000(5.0e+07) connections in 10000000(1.0e+07) objects.
======speed test in massive amount ends======

======edge test with 1000 objects starts======
it takes 5083 random edges to connect 1000 objects.
0.000134 seconds has elapsed.
======edge test with 1000 objects ends======

======edge test with 10000 objects starts======
it takes 48564 random edges to connect 10000 objects.
0.001275 seconds has elapsed.
======edge test with 10000 objects ends======

======edge test with 100000 objects starts======
it takes 517264 random edges to connect 100000 objects.
0.024069 seconds has elapsed.
======edge test with 100000 objects ends======

======edge test with 1000000 objects starts======
it takes 7614595 random edges to connect 1000000 objects.
0.300460 seconds has elapsed.
======edge test with 1000000 objects ends======

======edge test with 10000000 objects starts======
it takes 86188798 random edges to connect 10000000 objects.
8.864039 seconds has elapsed.
======edge test with 10000000 objects ends======
*/
