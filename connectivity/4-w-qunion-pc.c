#include <stdio.h>
#include <stdlib.h>
#include "connectivity.h"

/****************************************
 * @ingroup Connectivity
 * @defgroup WeightedQuickUnionWithPathCompression
 * @brief 连接问题算法4: Weighted-quick-union-with-path-compression算法。
 * 
 * ###改进#
 * 
 * 算法设计的最高目标是使算法具有线性的效率。
 * 那么，有没有可能找到一种具有确定的线性效率的连接问题算法呢?
 * (Weighted-quick-union算法的效率只是逼近线性，并不能在任何情况下都保证线性)
 * 
 * 根据算法研究者历来的经验可知，要找到这样的算法是极端困难的，
 * 目前还没有能线性解决连接问题的算法。
 * 
 * 虽然完美的算法难以达到，但是思考如何逼近完美算法常常有助于改进现有的算法。
 * 
 * 观察连接问题的前三种算法可以发现，
 * 对于联合操作来说，使用树型数据结构效率最高;
 * 对于搜索操作来说，子节点与根节点之间的距离越短越好。
 * 由此可知，对连接问题来说，最理想的算法应该保证树的高度不超过1。
 * 
 * 因此，Weighted-quick-union算法的优化方向就是尽量保证树的高度不超过1。
 * 要达到这个目的，比较显然的一种方法就是路径压缩(path compression)。
 * 
 * ###算法描述#
 * 
 * 路径压缩方法旨在使Weighted-quick-union树型数据结构中的每个子节点都直接指向根节点。
 * 要达到完美的效果，路径压缩方法应在每次联合操作后遍历新生成的树，
 * 将树中的所有子节点直接连接到根节点上。
 * 这种做法的开销显然太大。
 * 其原因在于Weighted-quick-union算法使用的简单树结构导致的两个问题:
 * -# 以根节点为起点无法找到任何子节点。
 * -# 判断一个节点的归属，只能通过追溯根节点的方式。
 * 
 * 这两个问题意味只有遍历整个存储数组，追溯每个节点的根节点才能遍历一个树，
 * 要将树的子节点直接连接到根节点上还需要另外一次遍历，
 * 这样的开销显然是无法让人接受的。
 * 
 * 因此，完美的路径压缩是不可取的，只能采用其他妥协的方案(即只压缩树的一部分)。
 * 其中一种方案是在Weighted-quick-union算法的搜索操作之后进行路径压缩。
 * 这种方法只压缩当前输入对象->根节点的路径，放弃对整个树的压缩。
 * 相对于完美的路径压缩，这种方法省去了对整个存储数组的遍历和追溯根节点的过程(由搜索操作完成)。
 * 所以，这种方法实际上只增加一次(两次)遍历，即将当前路径上的所有节点直接连接到根节点上所需的遍历。
 * 
 * ###状态迁移#
 * 
 * 容易从Weighted-quick-union算法的状态迁移推得，略。
 * 
 * @{
 ****************************************/

#ifdef DOC_COMPILE

/**
 * @brief Weighted-quick-union-with-path-compression算法实现
 * 
 * ###效率计算#
 * 
 * 要从理论上验证该算法是否比Weighted-quick-uniopn算法的效率更高是比较困难的，
 * 从实践经验来看，本算法的的效率稍高。
 * 
 * ###最坏情况#
 * 
 * 在Weighted-quick-union算法最坏情况的基础上避免路径压缩，即可得到本算法的最坏情况。
 * 
 * 观察Weighted-quick-union最坏情况例子的一部分:
 * @dotfile weighted-quick-union-worst-graph-2.gv
 * @dotfile weighted-quick-union-worst-graph-3.gv
 * 可以发现，在Weighted-quick-union算法中，从0-树和4-树中分别选出任意一个节点组成输入对，
 * 即可使两树结合成为一个高增增加1的新树。
 * 
 * 但在本算法中，随意的输入对很可能会触发路径压缩，输入对3-7会使0-树和4-树结合成如下的样子:
 * @dotfile weighted-quick-union-pc-good-graph.gv
 * 
 * 如果将输入对的对象限定为两树的根节点，例如: 0-4，则可得到的与Weighted-quick-union算法一样的结果。
 * 
 * 因此，在Weighted-quick-union最坏情况的基础上，再加上输入对的对象必须是树的根节点的限制，
 * 即可得到本算法的最坏情况(减半路径压缩法的最坏情况也一样)。
 * 
 */
int main() 
{
    int i, j, k, l, tmp, p, q, id[N], sz[N];
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
        // 将追溯经过的所有节点指向根节点
        k = p;
        while (k != id[k]) {
            tmp = id[k];
            id[k] = i;
            k = tmp;
        }
        // 搜索操作: 追溯后一个对象的根节点(j最终等于根节点的序号)
        for (j = q; j != id[j]; j = id[j]);
        // 将追溯经过的所有节点指向根节点
        l = q;
        while (l != id[l]) {
            tmp = id[l];
            id[l] = j;
            l = tmp;
        }
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

static void w_qunion_pc_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot);
static void w_qunion_pc_union_operation(struct storage_with_tree_size *storage, int proot, int qroot);

struct storage_with_tree_size *w_qunion_pc_new_storage(size_t object_num) {
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

void w_qunion_pc_delete_storage(struct storage_with_tree_size *storage) {
    if (storage != NULL) {
        free(storage->data);
        free(storage->tree_size);
        free(storage);
    }
    return;
}

bool w_qunion_pc_is_new_connection(struct storage_with_tree_size *storage, int p, int q) {
    int proot, qroot;
    w_qunion_pc_find_operation(storage, p, q, &proot, &qroot);
    if (proot == qroot) return false;
    w_qunion_pc_union_operation(storage, proot, qroot);
    return true;
}

static void w_qunion_pc_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot) {
    int i, original_parent;
    
    for (i = p; i != storage->data[i]; i = storage->data[i]);
    *proot = i;
    i = p;
    while (i != storage->data[i]) {
        original_parent = storage->data[i];
        storage->data[i] = *proot;
        i = original_parent;
    }
    
    for (i = q; i != storage->data[i]; i = storage->data[i]);
    *qroot = i;
    i = q;
    while (i != storage->data[i]) {
        original_parent = storage->data[i];
        storage->data[i] = *proot;
        i = original_parent;
    }
    
    return;
}

static void w_qunion_pc_union_operation(struct storage_with_tree_size *storage, int proot, int qroot) {
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
 * @} -- WeightedQuickUnionWithPathCompression
 ****************************************/