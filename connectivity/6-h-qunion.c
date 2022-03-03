#include <stdio.h>
#include <stdlib.h>
#include "connectivity.h"

/****************************************
 * @ingroup Connectivity
 * @defgroup HeightedQuickUnion
 * @brief 连接问题算法6: Height-quick-union算法。
 * 
 * ###改进#
 * 
 * 从Weighted-quick-union算法的分析可知，
 * 提高Quick-union算法效率(避免最坏情况)的关键在于压制树的高度。
 * 
 * Quick-union算法的联合操作通过将节点数较少的树连接到节点数较多的树上的方法，
 * 达到压制树高度的效果。
 * 此处，我们尝试一个更直接的方法: 以树的高度为判断依据，
 * 将高度较小的树连接到高度较大的树上，达到压制树高度的效果。
 * 我们将这个算法称为Heighted-quick-union。
 * 
 * Heighted-quick-union算法的基本框架和Weighted-quick-union算法保持一致，
 * 两者只在数据结构和联合操作上有一些区别。
 * 
 * ###数据结构#
 * 
 * 本算法将Weighted-quick-union中用于存储树的节点数的数组改用于存储树的高度。
 * 在初始状态下，每个元素(即只包含单个结点的树)的高度都是0。
 * 
 * ###算法描述#
 * 
 * Weighted-quick-union算法的分析已经给出了联合操作中树的高度的变化规律，
 * 如下:
 * | 与输入对对应的树的情况 | 新树的情况 |
 * | :------------------: | :-------: |
 * | 两个树的高度不相等 | 高度等于较高的输入树的高度 |
 * | 两个树的高度相等 | 高度等于输入树的高度+1 |
 * 
 * 可见，在本算法中，只有在输入的两个树的高度相等的情况下，新树的高度才会增加。
 * 根据这个原理，可以计算出新树的高度，详见算法实现。
 * 
 * @{
 ****************************************/

#ifdef DOC_COMPILE

/**
 * @brief Heighted-quick-union算法实现
 * 
 * ###最坏情况#
 * 
 * 本算法的最坏情况显然是树高度最高的情况，
 * 这与Weighted-quick-union算法的最坏情况一致。
 * 因此，可以推断本算法的效率和Weighted-quick-union算法的效率差不多。
 * 
 * ###效率计算#
 * 
 * 根据实践经验，Heighted-quick-union算法的效率确实和Weighted-quick-union算法的效率差不多。
 * 
 */
int main()
{
    int i, j, p, q, id[N], ht[N];
    // 初始化数组
    for (i = 0; i < N; i++)
    {
        id[i] = i;
        ht[i] = 0;
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
        // 前一个树的高度小于后一个树的高度时
        if (ht[i] < ht[j])
        {
            // 将前一个树连接到后一个树的根节点
            id[i] = j;
            // 后一个树的高度不变
        }
        // 前一个树的高度大于后一个数的高度时
        else if (ht[i] > ht[j])
        {
            // 将后一个树连接到前一个树的根节点
            id[j] = i;
            // 前一个树的高度不变
        }
        // 两个树的高度相等时
        else
        {
            // 将后一个树连接到前一个树的根节点
            id[j] = i;
            // 前一个树的高度加1
            ht[i]++;
        }
    }
    // 打印新连接关系
    printf(" %d %d\n", p, q);
}

#else // #ifdef DOC_COMPILE

static void h_qunion_find_operation(struct storage_with_tree_height *storage, int p, int q, int *proot, int *qroot);
static void h_qunion_union_operation(struct storage_with_tree_height *storage, int proot, int qroot);

struct storage_with_tree_height *h_qunion_new_storage(size_t object_num) {
    int *data = malloc(sizeof(*data) * object_num);
    int *tree_height = malloc(sizeof(*tree_height) * object_num);
    if (data != NULL && tree_height != NULL) {
        for (int i = 0; i < object_num; i++) {
            data[i] = i;
            tree_height[i] = 0;
        }
        struct storage_with_tree_height *storage = malloc(sizeof(*storage));
        storage->data = data;
        storage->tree_height = tree_height;
        return storage;
    }
    return NULL;
}

void h_qunion_delete_storage(struct storage_with_tree_height *storage) {
    if (storage != NULL) {
        free(storage->data);
        free(storage->tree_height);
        free(storage);
    }
    return;
}

bool h_qunion_is_new_connection(struct storage_with_tree_height *storage, int p, int q) {
    int proot, qroot;
    h_qunion_find_operation(storage, p, q, &proot, &qroot);
    if (proot == qroot) return false;
    h_qunion_union_operation(storage, proot, qroot);
    return true;
}

static void h_qunion_find_operation(struct storage_with_tree_height *storage, int p, int q, int *proot, int *qroot) {
    int i;
    for (i = p; i != storage->data[i]; i = storage->data[i]);
    *proot = i;
    for (i = q; i != storage->data[i]; i = storage->data[i]);
    *qroot = i;
    return;
}

static void h_qunion_union_operation(struct storage_with_tree_height *storage, int proot, int qroot) {
    if (storage->tree_height[proot] < storage->tree_height[qroot]) {
        storage->data[proot] = qroot;
    } else if (storage->tree_height[proot] > storage->tree_height[qroot]) {
        storage->data[qroot] = proot;
    } else {
        storage->data[qroot] = proot;
        (storage->tree_height[proot])++;
    }
    return;
}

#endif // #ifdef DOC_COMPILE

/****************************************
 * @} -- HeightedQuickUnion
 ****************************************/