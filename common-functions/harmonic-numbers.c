#include <stdio.h>
#include <math.h>
#include <time.h>

/****************************************
 * @defgroup HarmonicNumbers
 * @brief 调和级数。
 * 
 * 调和级数(英文为harmonic numbers或harmonic series)是算法分析中常用的一种级数，
 * 其和以符号H_N表示，H_N = 1 + 1/2 + 1/3 + ... + 1/N
 * 
 * 调和级数H_N的值近似于自然对数lnN的值，
 * lnN的值等于函数1/x图形中，横坐标1到N区间内，弧线下方的面积，
 * H_N的值稍大于这个面积(见Algorithm In C插图2.2 p.42)。
 * 
 * H_N与lnN的近似关系如下:
 *     H_N ≈ lnN + γ + 1/(12N)
 * 其中，γ称为欧拉常数，γ = 0.57721...
 * 
 * @{
 ****************************************/

#define EULER_CONSTANT 0.5772156649

static double compute_cpu_time_used(clock_t start_time, clock_t end_time) {
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

/**
 * @brief 根据调和级数的定义计算具有N个项的调和级数的和。
 * 
 * @param N N
 * @return double H_N
 */
static double sum_harmonic_numbers_by_definition(int N) {
	double H_N = 0;
	for (int i = 1; i <= N; i++) {
		H_N += 1.0 / (double)i;
	}
	return H_N;
}

/**
 * @brief 根据近似公式计算具有N个项的调和级数的和。
 * 
 * @param N  N
 * @return double H_N
 */
static double sum_harmonic_numbers_by_approx(int N) {
	return log(N) + EULER_CONSTANT + 1.0 / (12.0 * N);
}

int main() {
	int N= 1024;
	double H_N;
	clock_t start_time, end_time;

	/*
	 * 以下测试在debian 11虚拟机上运行的结果如下:
	 *     it tooks 0.258415 seconds to compute H_N's value: 7.509176.
	 *     it tooks 0.007427 seconds to compute H_N's value: 7.508769.
	 * 可见，近似算法的速度比定义算法快得多。
	 */
	start_time = clock();
	for (int i = 0; i < 1e5; i++) {
		H_N = sum_harmonic_numbers_by_definition(N);
	}
	end_time = clock();
	printf("it tooks %f seconds to compute H_N's value: %f.\n", compute_cpu_time_used(start_time, end_time), H_N);

	start_time = clock();
	for (int i = 0; i < 1e5; i++) {
		H_N = sum_harmonic_numbers_by_approx(N);
	}
	end_time = clock();
	printf("it tooks %f seconds to compute H_N's value: %f.\n", compute_cpu_time_used(start_time, end_time), H_N);

	return 0;
}

/****************************************
 * @} -- HarmonicNumbers
 ****************************************/
