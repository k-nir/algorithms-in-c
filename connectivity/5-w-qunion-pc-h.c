#include <stdio.h>
#include <stdlib.h>
#include "connectivity.h"

/****************************************
 * @ingroup Connectivity
 * @defgroup WeightedQuickUnionWithPathCompressionByHalving
 * @brief 连接问题算法5: Weighted-quick-union-with-path-compression-by-halving算法。
 * 
 * ###算法描述#
 * 
 * 另一种路径压缩的办法是减半路径压缩法(path compression by halving)。
 * 该方法也在Weighted-quick-union算法的搜索操作之后运行，
 * 但与普通的路径压缩法不同，减半路径压缩法只将当前路径缩短一半。
 * 具体来说，减半路径压缩法将当前路径上的每个节点连接到其父对象的父对象，
 * 达到将路径总长度减半的目的。
 * 同一路经过足够多次减半压缩后，能达到与普通路径压缩一样的效果。
 * 
 * 相比普通的路径压缩，此方法省去了压缩路径所需的遍历(减半压缩在追溯过程中就能完成)。
 * 
 * ###状态迁移#
 * 
 * 容易从Weighted-quick-union算法的状态迁移推得，略。
 * 
 * @{
 ****************************************/

#ifdef DOC_COMPILE

/**
 * @brief Weighted-quick-union-with-path-compression-by-halving算法实现
 * 
 * ###效率计算#
 * 
 * 要从理论上验证该算法是否比Weighted-quick-uniopn算法的效率更高是同样是比较困难的，
 * 从实践经验来看，本算法是Weighted-quick-union算法的变种中效率最高的。
 * 
 * ###最坏情况#
 * 
 * 同Weighted-quick-union-with-path-compression算法。
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
        for (i = p; i != id[i]; i = id[i]) {
            // 压缩追溯经过的节点
            id[i] = id[id[i]];
        }
        
        // 搜索操作: 追溯后一个对象的根节点(j最终等于根节点的序号)
        for (j = q; j != id[j]; j = id[j]) {
            // 压缩追溯经过的节点
            id[i] = id[id[i]];
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

static void w_qunion_pc_h_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot);
static void w_qunion_pc_h_union_operation(struct storage_with_tree_size *storage, int proot, int qroot);

struct storage_with_tree_size *w_qunion_pc_h_new_storage(size_t object_num) {
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

void w_qunion_pc_h_delete_storage(struct storage_with_tree_size *storage) {
    if (storage != NULL) {
        free(storage->data);
        free(storage->tree_size);
        free(storage);
    }
    return;
}

bool w_qunion_pc_h_is_new_connection(struct storage_with_tree_size *storage, int p, int q) {
    int proot, qroot;
    w_qunion_pc_h_find_operation(storage, p, q, &proot, &qroot);
    if (proot == qroot) return false;
    w_qunion_pc_h_union_operation(storage, proot, qroot);
    return true;
}

static void w_qunion_pc_h_find_operation(struct storage_with_tree_size *storage, int p, int q, int *proot, int *qroot) {
    int i;
    
    for (i = p; i != storage->data[i]; i = storage->data[i]) {
        storage->data[i] = storage->data[storage->data[i]];
    }
    *proot = i;
    
    for (i = q; i != storage->data[i]; i = storage->data[i]) {
        storage->data[i] = storage->data[storage->data[i]];
    }
    *qroot = i;
    
    return;
}

static void w_qunion_pc_h_union_operation(struct storage_with_tree_size *storage, int proot, int qroot) {
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
 * @} -- WeightedQuickUnionWithPathCompressionByHalving
 ****************************************/