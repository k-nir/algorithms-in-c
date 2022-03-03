#include <stdio.h>
#include <stdlib.h>
#include "connectivity.h"

/****************************************
 * @ingroup Connectivity
 * @defgroup WeightedQuickUnion
 * @brief 连接问题算法3: Weight-quick-union算法。
 * 
 * ###改进#
 * 
 * 观察Quick-union算法的最坏情况可以发现，
 * 在最坏情况下，每次联合操作时，前一个树(输入对中前一个对象所在的树)的高度都会增加1，
 * 后一个树(输入对中后一个对象所在的树)的高度总是为0。
 * 
 * 这是因为Quick-union算法在进行联合操作时，
 * 固定将前一个树的根节点连接到后一个树的根节点下。
 * 在最坏情况下，这导致前一个树的高度线性增长。
 * 
 * 要改善这个问题，可以将按固定顺序连接前后树改为，
 * 每次连接时都将节点数较少的树连接到节点较多的树下。
 * 
 * 我们将这样改动后的Quick-union算法称为Weighted-quick-union算法。
 * 
 * ###数据结构#
 * 
 * 改动后的算法在联合操作时需要比较前后两树的节点数，
 * 这就需要在数据结构中增加记录树节点数的空间。
 * 
 * 长度为N的数组最多能容纳N个树(即每个元素都是一个独立的树)，
 * 因此树节点数的计数最多有N个。
 * 由此，我们需要新增一个长度为N的数组来存储树节点数。
 * 
 * ###算法描述#
 * 
 * 在连接问题的两个抽象操作中，
 * 搜索操作不会影响集合中元素的个数，只有联合操作会影响集合元素的个数。
 * 因此，树节点计数的更新应当是在联合操作中完成的。
 * 
 * -# 初始化数组
 *    
 *    Weighted-quick-union算法除了要初始化存储连接关系的数组外，
 *    还需要初始化存储树节点计数的数组(称为计数数组)。
 *    
 *    计数数组的序号与树的根节点对应，值为树的节点计数，
 *    即根节点序号为x的树的节点数存储在计数数组下序号为x的元素中。
 *    
 *    在初始阶段，存储数组中每个元素都是一个树，因此计数数组的每个元素的初始值都是1。
 * 
 * -# 接受输入，检查输入的对象对是否已连接
 *    
 *    Weight-quick-union算法的搜索操作与Quick-union算法的相同。
 * 
 * -# 对象对已连接时，什么也不做
 *    
 *    此处也与Quick-union算法相同。
 * 
 * -# 对象未连接时，连接对象，并打印输出
 *    
 *    Weighted-quick-Union算法在追溯到输入对的两个对象的根节点后，
 *    会比较两个数的节点个数，将节点较少的树的根节点连接到节点较多的树的根节点上。
 *    这样做并不能保证新生成的树的高度最小，因为节点多的树的高度不一定比节点少的树大，
 *    例:
 *        @dotfile more-nodes-less-height.gv
 *    
 *    上图中左侧的树由树(0--1, 0--2)和树(3--4)合并而来，共有5个节点，高度为2，
 *    右侧的树可由若干个与5有关的输入对得来，共有6个节点，但高度只有1。
 *    按照Weighted-quick-union算法连接左右两个树时，左侧树会被连接到右侧树的根节点下，
 *    新树的高度将会是3。反过来连接的话新树的高度会为2。
 *    
 *    所以，Weighted-quick-union算法的重点不是缩短树的高度，而是避免Quick-union算法的最坏情况。
 *    在Quick-union算法的最坏情况下，Weighted-quick-union会生成如下所示的树:
 *    @dotfile better-quick-union-worst.gv
 *    
 *    连接完成后，要计算新树的节点数，只需从计数数组中读出原来两个树的节点计数并相加，
 *    再存入新树的根节点即可。
 *    
 * -# 等待下一个输入
 * 
 * ###状态迁移#
 * 
 * 初始状态
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-0.gv
 * 
 * 输入: 输入连接2-3\n
 * 结果: 将集合{2}和{3}合并成{2, 3}
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-1.gv
 * 
 * 输入: 输入连接5-7\n
 * 结果: 将集合{5}和{7}合并成{5, 7}
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-2.gv
 * 
 * 输入: 输入连接5-0\n
 * 结果: 将集合{5, 7}和{0}合并成{0, 5, 7}
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-3.gv
 * 
 * 输入: 输入连接0-3\n
 * 结果: 将集合{0, 5, 7}和{2, 3}合并成{0, 2, 3, 5, 7}
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-4.gv
 * 
 * 输入: 输入连接7-3\n
 * 结果: 连接已存在
 * - 逻辑图
 * @dotfile weighted-quick-union-graph-5.gv
 * 
 * 
 * @{
 ****************************************/

#ifdef DOC_COMPILE

/**
 * @brief Weighted-quick-union算法实现
 * 
 * ###最坏情况#
 * 
 * 对于Weighted-quick-union算法来说，最坏的情况就是树的高度最高的情况。
 * (对Quick-union算法也是如此)
 * 
 * 要使树的高度最高，显然需要使用尽量多的节点，
 * 因此，最坏情况必然会将存储数组中的所有元素连接到一个树中。
 * 将N个对象连接到一个树中，需要N-1次联合操作。
 * 
 * 再来考虑Weight-quick-union算法进行联合操作时，树的高度的变化情况:
 * | 与输入对对应的树的情况 | 新树的情况 |
 * | :------------------: | :-------: |
 * | 两个树的高度不相等 | 高度等于较高的输入树的高度 |
 * | 两个树的高度相等 | 高度等于输入树的高度+1 |
 * 
 * 可以看出，要使由所有元素构成的树的高度最高，就要在每次联合操作中尽量保证两边树的高度相等，
 * 这样每次联合操作都能使新树的高度加一。
 * 
 * 以如下模式发生的联合操作，可以达到上述效果:
 * @dotfile weighted-quick-union-worst-graph-0.gv
 * @dotfile weighted-quick-union-worst-graph-1.gv
 * @dotfile weighted-quick-union-worst-graph-2.gv
 * @dotfile weighted-quick-union-worst-graph-3.gv
 * 
 * 上述操作首先把对象都两两联合到高度为1的树，
 * 再把高度为1的树两两联合为高度为2的树，
 * 以此类推，直到所有对象都被连接到一个树中。
 * 
 * 每一步都会使树的总数减少一半，高度增加1。
 * 由此可知，将N个对象连接到一个树中需要大约lgN步，最后得到的树的高度大约为lgN(考虑N不是2的整数幂的情况)。
 * 
 * 这就意味着，在最坏情况下，最高树形成后，追溯一对输入对根节点的过程最多可以包含大约2lgN次跳转。
 * 
 * __注:__
 * 在美国，lg习惯上表示底数为2的对数。
 * 在欧洲，lg一般与log同义，表示底数为10的对数。
 * 在算法讨论中，lg几乎总是表示底数为2的对数。
 * 
 * ###效率计算#
 * 
 * 假设对象共有N个，根据最坏情况可知，
 * Weighted-quick-union算法处理为M个输入链接关系最多需要2MlgN个单位时间。
 * 在大量数据量下，Weighted-quick-union算法的性能远优于Quick-union算法和Quick-find算法。
 * 
 * 根据实践经验，Weighted-quick-union算法基本上可以以线性时间解决实际问题，
 * 即Weighted-quick-union算法的耗时与输入的数据量几乎可成线性关系。
 * 
 */
int main() 
{
    int i, j, p, q, id[N], sz[N];
    // 初始化数组
    for (i = 0; i < N; i++) 
    {
        id[i] = i;
        sz[i] = 1;
    }
    // 读取输入对
    while (scanf("%d %d", &p, &q) == 2) 
    {
        // 搜索操作: 追溯前一个对象的根节点(i最终等于根节点的序号)
        for (i = p; i != id[i]; i = id[i]);
        // 搜索操作: 追溯后一个对象的根节点(j最终等于根节点的序号)
        for (j = q; j != id[j]; j = id[j]);
        // 两个对象属于同一个树时，什么也不做，等待下一个输入
        if (i == j) continue;
        // 前一个树的节点数少于后一个树的节点数时
        if (sz[i] < sz[j]) 
        {
            // 将前一个树连接到后一个树的根节点
            id[i] = j;
            // 更新后一个树的节点数
            sz[j] += sz[i];
        }
        // 前一个树的节点数大于等于后一个树的节点数时
        else 
        {
            // 将后一个树连接到前一个树的根节点
            id[j] = i;
            // 更新前一个树的节点数
            sz[i] += sz[j];
        }
        // 打印新连接关系
        printf(" %d %d\n", p, q);
    }
}

#else // #ifdef DOC_COMPILE

static void w_qunion_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot);
static void w_qunion_union_operation(struct storage_with_tree_size *storage, int proot, int qroot);

struct storage_with_tree_size *w_qunion_new_storage(size_t object_num) {
    int *data = malloc(sizeof(*data) * object_num);
    int *tree_size = malloc(sizeof(*tree_size) * object_num);
    if (data != NULL && tree_size != NULL) {
        for (int i = 0; i < object_num; i++) {
            data[i] = i;
            tree_size[i] = 1;
        }
        struct storage_with_tree_size *storage = malloc(sizeof(*storage));
        storage->data = data;
        storage->tree_size = tree_size;
        return storage;
    }
    return NULL;
}

void w_qunion_delete_storage(struct storage_with_tree_size *storage) {
    if (storage != NULL) {
        free(storage->data);
        free(storage->tree_size);
        free(storage);
    }
    return;
}

bool w_qunion_is_new_connection(struct storage_with_tree_size *storage, int p, int q) {
    int proot, qroot;
    w_qunion_find_operation(storage, p, q, &proot, &qroot);
    if (proot == qroot) return false;
    w_qunion_union_operation(storage, proot, qroot);
    return true;
}

static void w_qunion_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot) {
    int i;
    for (i = p; i != storage->data[i]; i = storage->data[i]);
    *proot = i;
    for (i = q; i != storage->data[i]; i = storage->data[i]);
    *qroot = i;
    return;
}

static void w_qunion_union_operation(struct storage_with_tree_size *storage, int proot, int qroot) {
    if (storage->tree_size[proot] < storage->tree_size[qroot]) {
        storage->data[proot] = qroot;
        storage->tree_size[qroot] += storage->tree_size[proot];
    } else {
        storage->data[qroot] = proot;
        storage->tree_size[proot] += storage->tree_size[qroot];
    }
    return;
}

#endif // #ifdef DOC_COMPILE

/****************************************
 * @} -- WeightedQuickUnion
 ****************************************/