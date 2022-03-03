#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

/****************************************
 * @defgroup IntGeLglgN
 * @brief 求大于等于lglgN的最小整数。
 * 
 * 设大于等于lglgN的最小整数为n，
 * 则: n-1 < lglgN <= n
 * 变形得: 2^{n-1} < lgN <= 2^n
 * 再变形得: 2^{2^{n-1}} < N <= 2^{2^n}
 * 
 * @{
 ****************************************/

static double compute_cpu_time_used(clock_t start_time, clock_t end_time) {
	return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

/**
 * @brief C数学函数实现。
 * 
 * @param N N
 * @return int 大于等于lglgN的最小整数
 */
static int compute_int_ge_lglgN_1(long N) {
	// 因为lg(1) = 0，所以lglgN中的N必须大于1
	assert(N > 1);

	double lglgN = log2(log2((double)N));
	return (int)ceil(lglgN);
}

/**
 * @brief 从int-gt-lgN发展来的实现。
 * 
 * @param N N
 * @return int 大于等于lglgN的最小整数
 */
static int compute_int_ge_lglgN_2(long N) {
	assert(N > 1);

	bool is2power;
	
	// 首先算出大于等于N的最小 *2次幂* 的指数(exp)
	int exp = 0;
	is2power = true;
	/*
	 * 把N连续除2，直到: N / 2^exp <= 1
	 * N / 2^exp < 1 (即等于0)时，2^exp > N，所以exp是大于等于N的最小2次幂的指数;
	 * N / 2^exp == 1 时，则需要判断2^exp是否等于N，
	 * 等于时，exp是大于等于N的最小2次幂的指数，
	 * 不等于时，exp+1才是大于等于N的最小2次幂的指数。
	 */
	while (N > 1) {
		/*
		 * 在连续除2的过程中，如果出现除不尽的情况，
		 * 就说明N具有不等于2的因子，即N不是2的幂。
		 * 在 N / 2^exp == 1 的情况下，如果N不是2的幂，则N一定大于2^exp，
		 * 即exp需要额外增加1。
		 */
		if (is2power && N % 2 != 0) is2power = false;
		N >>= 1; // 等价于: N /= 2
		exp++;
	}
	if (N == 1 && !is2power) exp++;

	/*
	 * 再算出大于等于上述最小2次幂指数的 *2次幂次幂* 的指数的指数(exp_on_exp)。
	 * 我们最终的目标是要计算出大于等于N的最小2次幂次幂(即指数是2次幂的2次幂)，
	 * 此时我们已经知道了大于等于N的最小2次幂(及其指数exp)，
	 * 接下来只需要算出 *大于等于exp的最小2次幂* (即最小2次幂次幂的指数)，
	 * 即可得到n(最小2次幂次幂的指数的指数)。
	 */
	int exp_on_exp = 0;
	is2power = true;
	// 求大于等于exp的最小2次幂的过程与求大于等于N的最小2次幂的过程是一样的。
	while (exp > 1) {
		if (is2power && exp % 2 != 0) is2power = false;
		exp >>= 1; // 等价于: exp /= 2
		exp_on_exp++;
	}
	if (exp == 1 && !is2power) exp_on_exp++;

	return exp_on_exp;
}

/**
 * @brief 使用double类型的直接实现。
 * 
 * 根据式子:
 *     2^{n-1} < lgN <= 2^n
 * 可知，n是大于等于lgN的 *最小2次幂* 的指数。
 * 
 * 据此，求解n的过程可以分为两步: 
 *     1.求出大于等于lgN的最小2次幂
 *     2.求出上述2次幂的指数(即n)
 * 
 * 然而，在不使用log()函数的情况下上述思路是不可行的。
 * 
 * 根据式子:
 *     2^{2^{n-1}} < N <= 2^{2^n}
 * 可知，n是大于等于N的 *最小2次幂次幂* 的指数的指数。
 * 
 * 据此，求解n的过程应分为两步分:
 *     1.求出大于等于N的最小2次幂次幂
 *     2.求出上述2次幂次幂的指数的指数(即n)
 * 
 * 观察2^{2^n}的值: 2, 4, 16, 256, ...
 * 可以发现: 2^{2^n} = 2^{2^{n-1}} * 2^{2^{n-1}}
 * 据此，可以快速地计算出2^{2^n}的值。
 * 比较N和计算出的2^{2^n}值即可找出大于等于N的最小2次幂次幂，
 * 同时也能得到n的值。
 * 
 * @param N N
 * @return int 大于等于lglgN的最小整数
 */
static int compute_int_ge_lglgN_3(long N) {
	assert(N > 1);
	
	double dN = (double)N; // 以double类型表示的N
	int n = 0; // 2^{2^n}中的n
	double divisor = 2; // 与n对应的2次幂次幂的值
	/*
	 * dN / divisor == 1时，表示divisor == dN
	 * dN / divisor < 1时，表示divisor > dN
	 */
	while (dN / divisor > 1) {
		/*
		 * 2^{2^n}的值是本实现用到的所有值中的最大值。
		 * 在long类型的长度为64位的平台上，N的最大值是2^63-1，
		 * 大于等于该值的最小2次幂次幂是2^{2^6}(即2^64)，
		 * 因此divisor可能具有的最大值是2^64，
		 * 2^64约等于1.84e19，在double的范围之内。
		 * 因此，N可以取long范围内的所有正值。
		 */
		divisor *= divisor;
		n++;
	}

	return n;
}

/**
 * @brief 只用整型类型的直接实现。
 * 
 * 在double实现的基础上做最小的修改，得到的只使用整型的实现版本。
 * 
 * 整型算数与浮点算术之间最大的区别在于整型算术会直接截断小数。
 * 在double实现中，根据dN / divisor == 1就可以断定dN == divisor，
 * 但在整型实现中，dN / divisor == 1不是dN == divisor的充分条件。
 * 
 * @param N N
 * @return int 大于等于lglgN的最小整数
 */
static int compute_int_ge_lglgN_4(long N) {
	assert(N > 1 && N <= (LONG_MAX >> 1) + 1);

	int n = 0; // 2^{2^n}中的n
	long divisor = 2; // 与n对应的2次幂次幂的值
	while (N / divisor > 1) {
		/*
		 * 2^{2^n}的值是本实现可能用到的所有值中的最大值。
		 * 在long类型的长度为64位的平台上，N的最大值是2^63-1，
		 * 大于等于该值的最小2次幂次幂是2^{2^6}(即2^64)，
		 * 超出了long的表示范围，
		 * 小于等于2^63-1的最大2次幂次幂是2^{2^5}(即2^32)。
		 * 因此N的范围是: 1 < N <= 2^32
		 */
		divisor *= divisor;
		n++;
	}
	/*
	 * while循环结束后，N / divisor或者等于1，或者等于0，
	 * 等于0时，divisor > N一定成立，divisor即大于等于N的最小2次幂次幂；
	 * 等于1时，有两种情况:
	 *     1.divisor == N，此时divisor即大于等于N的最小2次幂次幂；
	 *     2.divisor < N，此时divisor显然不是大于等于N的最小2次幂次幂，而是小于N的最大2次幂次幂，
	 *       所以divisor需要再平方一次才能成为大于等于N的最小2次幂次幂(也就是使n加1)。
	 */
	if (N > divisor) n++;

	return n;
}

/**
 * @brief 最佳实现。
 * 
 * 最佳实现是没有N范围限制的整型实现。
 * 要使N的范围没有限制，就必须使实现内的所有值的可能最大值都不超过N，
 * 这就使得本实现必须避免直接表示2^{2^n}。
 * 
 * 要避免直接表示2^{2^n}，就要避免之前实现中divisor的2次方增长。
 * 在之前的实现中，于divisor的2次方增长形成对照的是N的不变，
 * 两者的主要应用都在式子: N / divisor 中，
 * 显然，在该式中，在结果不变的前提下，要使divisor的增幅变小，只有使N也相应变小。
 * 
 * 本实现使用增量除法的方法减小N，抑制divisor的2次方增长。
 * 以求大于等于65537的最小2次幂次幂为例，观察之间的实现，可以发现历次比较如下:
 *     N = 65537, divisor = 2^{2^n}
 *     1.65537 / 2 = 32768, n = 0
 *     2.65537 / 4 = 16384, n = 1
 *     3.65537 / 16 = 4096, n = 2
 *     4.65537 / 256 = 256, n = 3
 *     5.65537 / 65536 = 1, n = 4
 * 
 * 如果改用增量除法，历次比较的情况会变为:
 *     N = 65537 / 2^{2^{n-1}}, divisor = 2^{2^{n-1}}
 *     1.65537 / 2 = 32768, n = /
 *     2.32768 / 2 = 16384, n = 1
 *     3.16384 / 4 = 4096, n = 2
 *     4.4096 / 16 = 256, n = 3
 *     5.256 / 256 = 1, n = 4
 * 
 * 增量除法的原理来自以下式子:
 *     2^{2^n} = 2^{2^{n-1}} * 2^{2^{n-1}}
 * 根据此式，可得:
 *     N / 2^{2^n} = N / 2^{2^{n-1}} / 2^{2^{n-1}}
 * 即N除一次2^{2^n}可转化为N除两次2^{2^{n-1}}，
 * 将两次除2^{2^{n-1}}中的一次融入N，另一次留在divisor中，
 * 就避免了2^{2^n}在实现中直接出现。
 * 由于2^{2^{n-1}} < N，增量除法实现中出现的最大值一定是N。
 * 
 * 参考:
 * 
 * 2^{2^n}值表:
 * 
 * | n   | 2^n | 2^{2^n} |
 * | :-: | :-: | :-----: |
 * | 0   | 1   | 2^1 = 2 |
 * | 1   | 2   | 2^2 = 4 |
 * | 2   | 4   | 2^4 = 16 |
 * | 3   | 8   | 2^8 = 256 |
 * | 4   | 16  | 2^16 = 65536 |
 * | 5   | 32  | 3^32 = 4294967296 |
 * 
 * 65537(2^{2^4}+1)的增量除法表
 * 
 * | 增量除法   | 普通除法  | 结果   | 2^{2^n} | n   | 增量除数的指数 |
 * | :-----:   | :------:  | :-:   | :-----: | :-: | :---------: |
 * | /         | 65537 / 2 | 32768 | 2       | 0   | /  |
 * | 32768 / 2 | 65537 / 4 | 16384 | 4       | 1   | 1  |
 * | 16384 / 4 | 65537 / 16 | 4096 | 16      | 2   | 2  |
 * | 4096 / 16 | 65537 / 256 | 256 | 256     | 3   | 4  |
 * | 256 / 256 | 65537 / 65536 | 1 | 65536   | 4   | 8  |
 * 
 * 65535(2^{2^4}-1)的增量除法表
 * 
 * | 增量除法   | 普通除法  | 结果   | 2^{2^n} | n   | 增量除数的指数 |
 * | :-----:   | :------:  | :-:   | :-----: | :-: | :---------: |
 * | /         | 65535 / 2 | 32767 | 2       | 0   | /  |
 * | 32767 / 2 | 65535 / 4 | 16383 | 4       | 1   | 1  |
 * | 16383 / 4 | 65535 / 16 | 4095 | 16      | 2   | 2  |
 * | 4095 / 16 | 65535 / 256 | 255 | 256     | 3   | 4  |
 * | 255 / 256 | 65535 / 65536 | 0 | 65536   | 4   | 8  |
 * 
 * 2147483647(2^31-1)的增量除法表
 * 
 * | 增量除法        | 普通除法       | 结果        | 2^{2^n} | n   | 增量除数的指数 |
 * | :-----:        | :------:       | :-:        | :-----: | :-: | :---------: |
 * | /              | 2147483647 / 2 | 1073741823 | 2       | 0   | /  |
 * | 1073741823 / 2 | 2147483647 / 4 | 536870911  | 4       | 1   | 1  |
 * | 536870911 / 4  | 2147483647 / 16 | 134217727 | 16      | 2   | 2  |
 * | 134217727 / 16 | 2147483647 / 256 | 8388607  | 256     | 3   | 4  |
 * | 8388607 / 256  | 2147483647 / 65536 | 32767  | 65536   | 4   | 8  |
 * | 32767 / 65536  | 2147483647 / 4294967296 | 0 | 4294967296 | 5 | 16 |
 * 
 * @param N N
 * @return int 大于等于lglgN的最小整数
 */
static int compute_int_ge_lglgN_5(long N) {
	assert(N > 1);
	
	/* 
	 * N / 2^{2^n}
	 * 被转化为
	 * N / 2^{2^{n-1}} / 2^{2^{n-1}}
	 * 后，
	 * 在n=0的情况下，出现了负指数(2^{2^-1})，
	 * 为了避免处理负指数，本实现把n=0的情况作为特殊情况处理。
	 * 
	 * n=0时，使用旧式子进行计算和判断: N / 2^{2^n} = N / 2
	 */
	long d_N = N >> 1; // 等价: N / 2，d_N是增量除法中变化的N
	// N / 2 <= 1时，用之前实现中的旧逻辑判断n的值
	if (d_N <= 1) {
		if (N > 2) return 1; // 相当于: if (N > divisor) n++;
		else return 0;
	} 

	/* 
	 * n > 0时，用增量除法的新式子进行计算和判断: N / 2^{2^{n-1}} / 2^{2^{n-1}}
	 * 此处为了加快计算速度，没有跟踪增量除法的除数(即d_divisor *= d_divisor)，
	 * 而是跟踪了增量除法除数的指数(d_divisor_exp)，d_N >> d_divisor_exp等价于d_N / d_divisor。
	 */
	int n = 1; // n的值
	int d_divisor_exp = 1; // 增量除法除数的指数
	while ((d_N = d_N >> d_divisor_exp) > 1) { // 相当于 d_N /= 1 << d_divisor_exp，相当于: d_N /= d_divisor
		d_divisor_exp <<= 1; // 相当于: d_divisor_exp *= 2
		n++;
	}

	/* 
	 * 因为: d_N = N / d_divisor
	 * 所以: d_N / d_divisor = N / (d_divisor * d_divisor)
	 * d_N == 1时，说明: N / d_divisor^2 == 1
	 * 此时需要判断N是大于d_divisor^2还是等于d_divisor^2，
	 * N等于d_divisor^2时，说明d_divisor^2就是大于等于N的最小2次幂次幂，因此与其对应的n就是大于等于lglgN的最小整数；
	 * N大于d_divisor^2时，说明d_divisor^2还需要再次平方才能超过N，因此n要再加1才能成为大于等于lglgN的最小整数。
	 * 第二种情况的论证如下，
	 * 因为: N / d_divisor^2 = 1
	 * 所以: N / (d_divisor^2)^2 = 1 / d_divisor^2
	 * 因为d_divisor是2的2次幂次幂，最小值为2，所以: 1 / d_divisor^2 = 0
	 * 因此: N / (d_divisor^2)^2 = 0
	 * 即(d_divisor^2)^2是大于等于N的最小2次幂次幂。
	 */
	if (d_N == 1) {
		/*
		 * 根据上述推理可知，d_N == 1时，d_divisor^2必然小于等于N，
		 * 因此可以直接计算出来，不用担心溢出。
		 */
		long d_divisor_2 = 1 << (d_divisor_exp * 2);
		if (N > d_divisor_2) {
			n++;
		}
	}

	return n;
}

static void test(long N, int (*func)(long)) {
	int res = -1;
	clock_t start_time, end_time;

	start_time = clock();
	for (int i = 0; i < 1e7; i++) {
		res = func(N);
	}
	end_time = clock();
	printf("lglg(%ld) <= %d, cost %.3f s.\n", N, res, compute_cpu_time_used(start_time, end_time));
	return;
}

int main() {
	long N;

	/*
	 * 测试在debian 10虚拟机上的结果如下注，
	 * 可见，最佳实现都的效率最高，double实现的效率相当高。
	 */

	N = 2;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(2) <= 0, cost 0.091 s.
	 * lglg(2) <= 0, cost 0.038 s.
	 * lglg(2) <= 0, cost 0.026 s.
	 * lglg(2) <= 0, cost 0.035 s.
	 * lglg(2) <= 0, cost 0.022 s.
	 */

	N = 3;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(3) <= 1, cost 0.242 s.
	 * lglg(3) <= 1, cost 0.042 s.
	 * lglg(3) <= 1, cost 0.035 s.
	 * lglg(3) <= 1, cost 0.036 s.
	 * lglg(3) <= 1, cost 0.022 s.
	 */

	N = 4;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(4) <= 1, cost 0.090 s.
	 * lglg(4) <= 1, cost 0.047 s.
	 * lglg(4) <= 1, cost 0.035 s.
	 * lglg(4) <= 1, cost 0.067 s.
	 * lglg(4) <= 1, cost 0.030 s.
	 */
	
	N = 5;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(5) <= 2, cost 0.239 s.
	 * lglg(5) <= 2, cost 0.051 s.
	 * lglg(5) <= 2, cost 0.047 s.
	 * lglg(5) <= 2, cost 0.067 s.
	 * lglg(5) <= 2, cost 0.029 s.
	 */

	N = 1023;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(1023) <= 4, cost 0.240 s.
	 * lglg(1023) <= 4, cost 0.131 s.
	 * lglg(1023) <= 4, cost 0.074 s.
	 * lglg(1023) <= 4, cost 0.188 s.
	 * lglg(1023) <= 4, cost 0.059 s.
	 */

	N = 1024;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(1024) <= 4, cost 0.143 s.
	 * lglg(1024) <= 4, cost 0.139 s.
	 * lglg(1024) <= 4, cost 0.074 s.
	 * lglg(1024) <= 4, cost 0.195 s.
	 * lglg(1024) <= 4, cost 0.053 s.
	 */

	N = 1025;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(1025) <= 4, cost 0.240 s.
	 * lglg(1025) <= 4, cost 0.161 s.
	 * lglg(1025) <= 4, cost 0.074 s.
	 * lglg(1025) <= 4, cost 0.195 s.
	 * lglg(1025) <= 4, cost 0.053 s.
	 */

	N = 65535;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(65535) <= 4, cost 0.240 s.
	 * lglg(65535) <= 4, cost 0.177 s.
	 * lglg(65535) <= 4, cost 0.074 s.
	 * lglg(65535) <= 4, cost 0.217 s.
	 * lglg(65535) <= 4, cost 0.059 s.
	 */

	N = 65536;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(65536) <= 4, cost 0.088 s.
	 * lglg(65536) <= 4, cost 0.204 s.
	 * lglg(65536) <= 4, cost 0.074 s.
	 * lglg(65536) <= 4, cost 0.223 s.
	 * lglg(65536) <= 4, cost 0.056 s.
	 */

	N = 65537;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(65537) <= 5, cost 0.241 s.
	 * lglg(65537) <= 5, cost 0.222 s.
	 * lglg(65537) <= 5, cost 0.089 s.
	 * lglg(65537) <= 5, cost 0.224 s.
	 * lglg(65537) <= 5, cost 0.059 s.
	 */

	N = 12288; // 3*2^12，能触发12次求余。
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	test(N, compute_int_ge_lglgN_4);
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(12288) <= 4, cost 0.240 s.
	 * lglg(12288) <= 4, cost 0.169 s.
	 * lglg(12288) <= 4, cost 0.074 s.
	 * lglg(12288) <= 4, cost 0.207 s.
	 * lglg(12288) <= 4, cost 0.059 s.
	 */

	N = LONG_MAX;
	test(N, compute_int_ge_lglgN_1);
	test(N, compute_int_ge_lglgN_2);
	test(N, compute_int_ge_lglgN_3);
	// test(N, compute_int_ge_lglgN_4); // 超出范围
	printf("input out of range.\n");
	test(N, compute_int_ge_lglgN_5);
	putchar('\n');
	/*
	 * lglg(9223372036854775807) <= 6, cost 0.142 s.
	 * lglg(9223372036854775807) <= 6, cost 0.588 s.
	 * lglg(9223372036854775807) <= 6, cost 0.101 s.
	 * input out of range.
	 * lglg(9223372036854775807) <= 6, cost 0.075 s.
	 */

	return 0;
}

/****************************************
 * @} -- IntGeLglgN
 ****************************************/
