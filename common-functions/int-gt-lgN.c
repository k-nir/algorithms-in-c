#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <tgmath.h>
#include <assert.h>

/****************************************
 * @defgroup IntGtLgN
 * @brief 求大于lgN的最小整数的三种方法。
 * 
 * 大于lgN的最小整数等于N以二进制表示时具有的位数。
 * 
 * 相关证明见: 求进制转换后新进制下数的长度.pdf
 * 
 * @{
 ****************************************/

static double compute_cpu_time_used(clock_t start_time, clock_t end_time) {
	return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

/**
 * @brief c数学函数实现。
 * 
 * @param N N
 * @return int 大于lgN的最小整数
 */
static int compute_int_gt_lgN_1(int N) {
	assert(N >= 1);
	
	double lgN = log2((double)N + 1);
	return (int)ceil(lgN);
}

/**
 * @brief 乘法实现。
 * 
 * 设大于lgN的最小整数为n，可得: n-1 <= lgN < n
 * 即: 2^{n-1} <= N < 2^n
 * 据此，可将求解大于lgN的最小整数的问题转化为求解大于N的最小2次幂。
 * 
 * 该方法的优点是完全用整型计算，不涉及浮点数，比较简单。
 * 
 * @param N N
 * @return int 大于lgN的最小整数
 */
static int compute_int_gt_lgN_2(int N) {
	/*
	 * 因为N和power的类型都是int，
	 * power的值一定是2次幂且一定大于N，
	 * 所以N的值必须小于int类型所能表示的最大的2次幂。
	 * int类型的最大值是2^32-1，能表示的最大2次幂是INT_MAX / 2 + 1(相当于右移一位再加1)
	 */
	assert(N >= 1 && N < INT_MAX / 2 + 1);
	
	int power = 1; // 2^0
	int exp = 0;
	while (power < N) {
		power <<= 1; // 左移和*2效果相同，但速度更快
		exp++;
	}
	return exp;
}

/**
 * @brief 除法实现。
 * 
 * 由: 2^{n-1} <= N < 2^n
 * 可知: N = 2^{n-1} + b, 0 <= b < 2^{n-1}
 * 将上式两边除以2^n，得 N / 2^n = 2^{-1} + b / 2^n, 0 <= b / 2^n < 2^{-1}
 * 因为: 2^{-1} = 1/2, b / 2^n < 1/2
 * 所以: N / 2^n < 1
 * 
 * 同理可证: N / 2^{n-1} > 1
 * 
 * 所以，在整型除法中，N / 2^n = 0 , N / 2^{n-1} > 0
 * 
 * 显然，N / 2^n与用2连续除以N n次等价，
 * 结合上述结论可知，N被2除n-1次后大于0，被2除n次后等于0，
 * 也就是说，在将N反复除以2，直到结果等于0的过程中，N被除的次数就是大于lgN的最小整数。
 * 
 * 据此，可将求解大于lgN的最小整数的问题转化为求N被2连续除后等于0所需的最小次数。
 * 
 * 该方法的优点是N的值域没有额外的限制，可以完全利用int类型。
 * 
 * @param N N
 * @return int 大于lgN的最小整数
 */
static int compute_int_gt_lgN_3(int N) {
	assert(N >= 1);

	int exp = 0;
	while (N > 0) {
		/*
		 * 有符号整形的除2比乘2慢很多，
		 * 这是因为负数在整型除法中的取整与位移的行为不符。
		 * 
		 * 以长度为4的有符号整型-7(二进制表示为1001)为例，
		 * 右移一位(左侧补符号位1)后得到的是-4(1100)，
		 * 而-7/2的正确结果应为-3。
		 * 
		 * 编译器解决这个问题的通常做法是在对负数进行右移之前，
		 * 先把负数加上1，
		 * 对偶负数来说，加上1只是把最低位从0变成1，该位会在右移中被消耗掉，
		 * 因此没有影响。
		 * 对奇负数来说，加上1会使其变为绝对值小1的偶负数，右移后得到该偶负数的1/2值，
		 * 即获得了正确的除法行为。
		 * 
		 * 可见，有符号整型的/2会比*2多用一些指令，因此较慢，
		 * 要提高/2的速度，可使用无符号整型。
		 * 
		 * 在本函数中，N一定是正数，因此可以直接用右移代替除法。
		 */
		N >>= 1;
		exp++;
	}
	return exp;
}

int main() {
	int N = 1025;
	int res = -1;
	clock_t start_time, end_time;
	 
	 /*
	  * 在debian 10虚拟机上用gcc -O0编译本文件，运行的结果如下:
	  *     Smallest integer larger than lg1025 is 11, computation took 0.110808 seconds.
	  *     Smallest integer larger than lg1025 is 11, computation took 0.122945 seconds.
	  *     Smallest integer larger than lg1025 is 11, computation took 0.118669 seconds.
	  * 可见c数学函数实现速度最快。
	  * 将实现2和3中的位移替换成乘除法，得到的结果如下:
	  *     Smallest integer larger than lg1025 is 11, computation took 0.109138 seconds.
	  *     Smallest integer larger than lg1025 is 11, computation took 0.118922 seconds.
	  *     Smallest integer larger than lg1025 is 11, computation took 0.159841 seconds.
	  * 可见有符号整型除法对速度的影响。
	  */
	start_time = clock();
	for (int i = 0; i < 1e7; i++) {
		res = compute_int_gt_lgN_1(N);
	}
	end_time = clock();
	printf("Smallest integer larger than lg%d is %d, computation took %f seconds.\n", N, res, compute_cpu_time_used(start_time, end_time));
	
	start_time = clock();
	for (int i = 0; i < 1e7; i++) {
		res = compute_int_gt_lgN_2(N);
	}
	end_time = clock();
	printf("Smallest integer larger than lg%d is %d, computation took %f seconds.\n", N, res, compute_cpu_time_used(start_time, end_time));

	start_time = clock();
	for (int i = 0; i < 1e7; i++) {
		res = compute_int_gt_lgN_3(N);
	}
	end_time = clock();
	printf("Smallest integer larger than lg%d is %d, computation took %f seconds.\n", N, res, compute_cpu_time_used(start_time, end_time));

	return 0;
}

/****************************************
 * @} -- IntGtLgN
 ****************************************/
