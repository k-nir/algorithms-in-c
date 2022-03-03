#include <stdio.h>
#include <math.h>
#include <time.h>

/****************************************
 * @defgroup FibonacciNumbers
 * @brief 斐波那契数列。
 * 
 * 斐波那契数列是算法分析中常用的数列，
 * 其通项以F_N表示，定义如下:
 *     F_N = F_{N-1} + F_{N-2}
 * 其中，
 *     N >= 2
 *     F_0 = 0, F_1 = 1
 * 
 * 斐波那契数列与黄金分割比φ之间有密切的关系，
 * 斐波那契数列中相邻两项的比趋近于: 
 *     φ =（1 + sqrt(5)）/ 2 ≈ 1.61803...
 * 
 * 分析表明，斐波那契数列的第N个项的值F_N等于以下式子:
 *     φ^N/sqrt(5)
 * 四舍五入成整数后得到的值。
 * 
 * @{
 ****************************************/

#define GOLDEN_RATIO ((1.0 + sqrt(5.0)) / 2)

static double compute_cpu_time_used(clock_t start_time, clock_t end_time) {
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

/**
 * @brief 以定义计算F_N。
 * 
 * @param N N
 * @return int F_N
 */
static int compute_fibonacci_numbers_by_definition(int N) {
    if (N == 0) return 0;
    int F_N = 1;
    int pre = 0;
    for (int i = 1; i < N; i++) {
        int now_old = F_N;
        F_N += pre;
        pre = now_old;
    }
    return F_N;
}

/**
 * @brief 用黄金分割比公式计算F_N。
 * 
 * @param N N
 * @return int F_N
 */
static int compute_fibonacci_numbers_by_golden_ratio(int N) {
    return (int)round((pow(GOLDEN_RATIO, (double)N) / sqrt(5.0)));
}

int main() {
	int N = 32;
	int F_N;
	clock_t start_time, end_time;

	/*
	 * 以下测试在debian 11虚拟机上运行的结果如下:
	 *     it took 0.006290 seconds to compute F_N's value: 2178309.
     *     it took 0.002400 seconds to compute F_N's value: 2178309.
	 */
	start_time = clock();
    for (int i = 0; i < 1e5; i++) {
	    F_N = compute_fibonacci_numbers_by_definition(N);
    }
	end_time = clock();
	printf("it took %f seconds to compute F_N's value: %d.\n", compute_cpu_time_used(start_time, end_time), F_N);

	start_time = clock();
    for (int i = 0; i < 1e5; i++) {
	    F_N = compute_fibonacci_numbers_by_golden_ratio(N);
    }
	end_time = clock();
    printf("it took %f seconds to compute F_N's value: %d.\n", compute_cpu_time_used(start_time, end_time), F_N);

	return 0;
}

/****************************************
 * @} -- FibonacciNumbers
 ****************************************/
