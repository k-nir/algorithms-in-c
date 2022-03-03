#include <stdio.h>
#include <stdlib.h>
#include "connectivity.h"

/****************************************
 * @ingroup Connectivity
 * @defgroup QuickUnion
 * @brief 连接问题算法2: Quick-union算法。
 * 
 * ###数据结构#
 * 
 * Quick-union算法与Quick-find算法相似，也用数组存储连接信息，
 * 同样用数组元素本身代表对象，用数组元素的值代表连接关系。
 * 
 * 不同之处在于，在Quick-union算法中，元素的值的作用类似于指针，
 * 属于同一个集合的对象通过元素的值形成一个树，
 * 充当根节点的对象的值为自身的序号，充当其他节点的对象的值为自己的父节点的序号。
 * 由此，从集合中的任意一个对象开始追溯父节点，最后一定会来到该集合的根节点。
 * 
 * 在Quick-union算法中，
 * 有连接关系的两个对象可以追溯到同一个根节点，没有连接关系的两个对象不能追溯到同一个根节点。
 * 
 * ###算法描述#
 * 
 * -# 初始化数组
 *    
 *    在开始接受输入之前，连接程序不知道对象间的任何连接关系，
 *    此时数组中的所有元素都各自组成一个无连接集合。
 *    
 *    对于只有一个元素的集合，该唯一元素必然是该集合的根节点，
 *    因此，初始化应将数组中的每个元素变成自己的根节点。
 *    
 *    要分辨一个元素是否是根节点，就必须使根节点元素的值与子节点元素的值有某种区分，
 *    即根节点元素的值应具有某种子节点元素的值所不具备的特性。
 *    使根节点元素的值等于自身的序号或使根节点元素的值等于-1，都能使根节点元素的值具备子节点元素的值不可能有的特性
 *    (不指向他元素的节点/只想不存在的元素(-1)的节点显然不能是子结点)，所以两种方法都能满足上述要求。
 *    
 *    Quick-union算法选择前一种方法，由此，Quick-union算法的数组初始化过程就是使数组中的每个元素的值等于自己的序号。
 * 
 * -# 接受输入，检查输入的对象对是否已连接
 *    
 *    要检查输入的对象是否已连接，需要追溯两个对象的根节点，并判断两者的根节点是否为同一个节点。
 *    
 *    追溯根节点的流程如下:
 *    -# 读取当前元素的值。
 *    -# 如果取到的值等于当前元素的序号，则追溯结束。
 *    -# 如果取到的值不等于当前元素的序号，则跳转到序号等于取到的值的元素，回到第一步。
 *    .
 *    
 *    本步骤与抽象操作中的 **搜索** 操作对应，可见Quick-union的搜索效率不太高。
 * 
 * -# 对象对已连接时，什么也不做
 *    
 *    与输入对中的两个对象对应的元素的根节点是同一个节点时，表示输入的对象已连接。
 * 
 * -# 对象未连接时，连接对象，并打印输出
 *    
 *    在Quick-union算法下使两个对象连接到一起，就是是两个对象成为同一个树的子节点。
 *    
 *    让两个对象处于同一个树的最简单的办法显然是使一个对象指向另一个对象
 *    (即一个对象的值等于另一个对象的序号)，但是要注意，这个简单方法是错误的。
 *    原因在于连接关系具有传递性，两个对象间的连接关系不仅限于两个对象之间，
 *    而是会扩散到两个对象所处的集合下的所有元素。
 *    
 *    所以，使两个对象连接到一起实际上意味着将两个对象所在的集合合并成一个集合，
 *    也就是将两个树合并成一个树。
 *    
 *    最简单的合并两个树的方法是把一个树的根节点变为另一个树的子节点，
 *    即使一个树的根节点元素的值等于另一个树的任意节点元素的序号。
 *    
 *    因此，连接两个对象需要经过以下步骤:
 *    -# 追溯一个对象的根节点。
 *    -# 使上述根节点等于另一个对象所属的树中任意元素的序号。
 *    .
 *    在第二步中，需要防止一个树的根节点被连接到自身的子节点上形成闭环结构的情况出现。
 *    因此，进行第二步时，必须判断第一部获得的根节点和其将要连接到的节点是否属于同一个树，
 *    属于同一个树时，不能进行连接操作，不属于同一个树时，才能连接。
 *    
 *    在之前的搜索操作中，我们已经追溯到了两个对象的根节点，并判断了两个对象是否属于同一个树，
 *    因此也就保证了数组中不会出现闭环结构。
 * 
 *    在具体实现中，本算法总是选择使前一个对象所属的树的根节点元素的值等于后一个对象所属的树的根节点元素的序号。
 *    
 *    连接操作就是抽象操作中的 **联合** 操作，
 *    从上文可知，只需更改一个根节点元素的值，即可完成Quick-union算法的联合操作，
 *    所以，Quick-union算法的联合操作效率很高，并因此得名。
 * 
 * -# 等待下一个输入
 *    
 * ###状态迁移#
 * 
 * 初始状态
 * - 逻辑图
 * @dotfile quick-union-graph-0.gv
 * - 实际数组
 * @dotfile quick-union-array-0.gv
 * 
 * 输入: 输入连接2-3\n
 * 结果: 将集合{2}和{3}合并成{2, 3}
 * - 逻辑图
 * @dotfile quick-union-graph-1.gv
 * - 实际数组
 * @dotfile quick-union-array-1.gv
 * 
 * 输入: 输入连接5-7\n
 * 结果: 将集合{5}和{7}合并成{5, 7}
 * - 逻辑图
 * @dotfile quick-union-graph-2.gv
 * - 实际数组
 * @dotfile quick-union-array-2.gv
 * 
 * 输入: 输入连接5-0\n
 * 结果: 将集合{5, 7}和{0}合并成{0, 5, 7}
 * - 逻辑图
 * @dotfile quick-union-graph-3.gv
 * - 实际数组
 * @dotfile quick-union-array-3.gv
 * 
 * 输入: 输入连接0-3\n
 * 结果: 将集合{0, 5, 7}和{2, 3}合并成{0, 2, 3, 5, 7}
 * - 逻辑图
 * @dotfile quick-union-graph-4.gv
 * - 实际数组
 * @dotfile quick-union-array-4.gv
 * 
 * 输入: 输入连接7-3\n
 * 结果: 连接已存在
 * - 逻辑图
 * @dotfile quick-union-graph-5.gv
 * - 实际数组
 * @dotfile quick-union-array-5.gv
 * 
 * 
 * @{
 ****************************************/

#ifdef DOC_COMPILE

/**
 * @brief Quick-union算法实现
 * 
 * ###效率计算#
 * 
 * Quick-union算法处理一个输入对时，首先追溯其中对象的根节点，
 * 一个对象与其根节点之相隔多少个子节点是不确定的。
 * 
 * 假设对象共有N个，一个对象与根节点之间最少相隔0个子节点(即对象本身就是根节点)，
 * 最多相隔N-2个子节点(即数组中所有元素组成一个链表，根节点在链表头，当前对象在链表尾)。
 * 在最好的情况下，搜索操作只需一次取值和比较即可追溯到一个对象的根节点;
 * 在最差的情况下，搜索操作需要进行N次取值和比较(链表中的每个元素都需要一个取值和比较)才能追溯到一个对象的根节点。
 * 
 * 根据实践经验，输入的连接关系数M > N时，Quick-union算法搜索操作的平均耗时大概是MN/2个单位时间(此算法联合操作是O(1)操作，忽略不计)。
 * Quick-union算法的效率可以说是相当好的，足以应付大规模的数据。
 * 
 * ###最坏情况#
 * 
 * 不过，Quick-union算法还是有有一些缺点，在比较坏的情况下，它的效率会显著下降。
 * 下面讨论Quick-union算法在最坏情况下的表现。
 * 
 * 假设Quick-union算法接收的输入依次为: 1-2, 2-3, 3-4 ...，
 * 则经过N-1个输入后，算法的数组中会形成一个由N个对象组成的呈直线状的树(类似链表)，
 * 如图:
 * @dotfile quick-union-graph-worst.gv
 * 
 * 此时，追溯对象1的根节点都需要进行N-1次跳转，追溯对象2的根节点需要进行N-2次跳转，
 * 以此类推，可知追溯[1,N]范围内的对象的根节点需要的平均跳转数为
 * \f[
 *     \frac{\overbrace{0 + 1 + \ldots + (N-1)}^N}{N}
 *     = \frac{\frac{N}{2} \cdot (N-1)}{N}
 *     = \frac{N-1}{2}
 * \f]
 * 
 * 假设在最坏的情况下，从第N个输入起，所有输入对都描述与对象1有关的旧连接，例如: 1-5, 1-10 ...,
 * 则Quick-union算法每次处理输入时，都至少需要跳转N-1次(用于追溯对象1的根节点)。
 * (注意这样的输入保证了对象的总数为N个(忽略0))
 * 
 * 因此，在形成链表后，再处理M个旧连接输入对需要的总跳转数为
 * \f[
 *     M(N-1)
 * \f]
 * 
 * 这个数字显然大于平均情况下的跳转数，再加上生成链表需要的总跳转数，差距还会更大。
 */
int main()
{
    int i, j, p, q, t, id[N];
    // 初始化数组
    for (i = 0; i < N; i++) id[i] = i;
    // 读取输入对
    while (scanf("%d %d", &p, &q) == 2) 
    {
        // 搜索操作: 追溯前一个对象的根节点(i最终等于根节点的序号)
        for (i = p; i != id[i]; i = id[i]);
        // 搜索操作: 追溯后一个对象的根节点(j最终等于根节点的序号)
        for (j = q; j != id[j]; j = id[j]);
        // 两个对象属于同一个树时，什么也不做，等待下一个输入
        if (i == j) continue;
        // 联合操作: 不属于同一个树时，使前一个元素的根节点指向后一个元素的根节点
        id[i] = j;
        // 打印新连接关系
        printf(" %d %d\n", p, q);
    }

    return 0;
}

#else // #ifdef DOC_COMPILE

static void qunion_find_operation(int *storage, int p, int q, int *proot, int *qroot);
static void qunion_union_operation(int *storage, int proot, int qroot);

int *qunion_new_storage(size_t object_num) {
    int *storage = malloc(sizeof(*storage) * object_num);
    if (storage != NULL) for (int i = 0; i < object_num; i++) storage[i] = i;
    return storage;
}

void qunion_delete_storage(int *storage) {
    if (storage != NULL) free(storage);
    return;
}

bool qunion_is_new_connection(int *storage, int p, int q) {
    int proot, qroot;
    qunion_find_operation(storage, p, q, &proot, &qroot);
    if (proot == qroot) return false;
    qunion_union_operation(storage, proot, qroot);
    return true;
}

static void qunion_find_operation(int *storage, int p, int q, int *proot, int *qroot) {
    int i;
    for (i = p; i != storage[i]; i = storage[i]);
    *proot = i;
    for (i = q; i != storage[i]; i = storage[i]);
    *qroot = i;
    return;
}

static void qunion_union_operation(int *storage, int proot, int qroot) {
    storage[proot] = qroot;
    return;
}

#endif // #ifdef DOC_COMPILE

/****************************************
 * @} -- QuickUnion
 ****************************************/