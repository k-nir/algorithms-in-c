#include <stdio.h>
#include <math.h>
#include <time.h>

/****************************************
 * @defgroup Factorial
 * @brief 阶乘。
 * 
 * 阶乘是离散数学中常用的工具，因此经常常熟现在算法分析中。
 * 阶乘也有一种近似式，称为斯特林公式，如下:
 *     lg(N!) ≈ NlgN - Nlg(e) + lg(sqrt(2πN))
 * 
 * 阶乘的值很容易变成天文数字，按照定义计算时计算量太大，
 * 用斯特林公式能很好地缓解这个问题。
 * 
 * 另外，斯特林公式给出的lg(N!)的近似值还能用来估计N!表示为二进制时具有的位数。
 * 在比较粗糙的估计中，可以直接将N!的二进制位数估为NlgN。
 * 
 * @{
 ****************************************/

/**
 * @brief 推测N!表示为二进制时具有的位数。
 * 
 * @param N N
 * @return int 位数
 */
static int reckon_factorial_binary_digits_number(int N) {
    return (int)ceil(N*log2(N) - N*log2(exp(1)) + log2(sqrt(2 * M_PI * N)));
}

/**
 * @brief 推测N!表示为十进制时具有的位数。
 * 
 * N!表示为十进制时具有的位数是log_10{N!}(论证见: 求进制转换后新进制下数的长度.pdf)，
 * 在斯特林公式的基础上使用换底公式即可计算出log_10{N!}的值:
 *     lg(N!) = log_10{N!} / log_10{2}
 *     log_10{N!} = log_10{2} * lg(N!)
 * 
 * @param N N
 * @return int 位数
 */
static int reckon_factorial_decimal_digits_number(int N) {
    return (int)(ceil(log10(2) * (N*log2(N) - N*log2(exp(1)) + log2(sqrt(2 * M_PI * N)))));
}

int main() {
    int N = 10;
    int digits;
    /*
     * 运行结果为:
     *     the number of digits of 10!'s binary representation is 22.
     *     the number of digits of 10!'s binary representation is 7.
     * 10! = 3628800，表示为二进制时有22位，十进制时有7位。
     */
    digits = reckon_factorial_binary_digits_number(N);
    printf("the number of digits of %d!'s binary representation is %d.\n", N, digits);
    digits = reckon_factorial_decimal_digits_number(N);
    printf("the number of digits of %d!'s decimal representation is %d.\n", N, digits);
    return 0;
}

/****************************************
 * @} -- Factorial
 ****************************************/
