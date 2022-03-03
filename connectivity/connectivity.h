#ifndef HEADER_CONNECTIVITY_H
#define HEADER_CONNECTIVITY_H

#include <stdbool.h>

/****************************************
 * @defgroup Connectivity
 * @brief Algorithms IN C第一章中的连接问题。
 * 
 * ###问题描述#
 * 
 * 设有一组可互相连接的对象，两个对象的之间的连接以"p-q"的形式表示，
 * 连接关系具有传递性: 如果对象p与对象q相连，对象q与对象r相连，则对象p与对象r相连。
 * 
 * 在计算机中，对象可被抽象为整数，对象间的连接可被抽象成为整数对(例如: "2 3")。
 * 
 * 现在要求设计一个根据历史输入判断对象间的连接是否已存在的程序，该程序循环接受整数对输入，
 * 每次接受输入时，都要根据之前的输入判断当前输入的两个对象是否已经有连接关系(即之前的输入是否已经暗示了这两个对象的连接关系)；
 * 两个对象之前没有连接关系时，程序需要打印该整数对，提示用户产生了新连接；两个对象之前已经有连接关系时，程序不打印任何信息，以此表示连接已存在。
 * 
 * ###问题的复杂度#
 * 
 * 设计算法时，准确地把握问题的复杂度是很重要的。
 * 
 * 以连接问题为例，本文的连接问题只要求程序判断输入的对象是否已连接，
 * 如果稍稍改动要求，使之变为计算两个对象之间有多少种连接方法的话，
 * 问题的复杂度就会极大地上升，解决后一个问题的算法与解决前一个问题的算法相比，
 * 会复杂得多，且需要从问题中提取并处理更多的信息。
 * 
 * 本文的连接问题非常精确地限定了问题，因此容易把握其复杂度。
 * 但在现实中，实际问题的本质往往难以一次看清，
 * 大多数时候对问题的理解都是在解决问题的过程中深化的，
 * 这就导致在设计算法的过程中，常常会出现设计进行到一半，
 * 发现当前算法提供的信息不足以解决问题的情况(或者比较乐观的情况——当前算法提供的信息能解决更复杂问题)。
 * 
 * 因此，设计者在设计算法的过程中，要时时注意问题的复杂度，
 * 并根据复杂度及时调整算法。
 * 
 * ###抽象操作#
 * 
 * 仔细理解问题后，可以发现，连接问题可以分成两个问题:
 * -# 接收新对象对时，如何判断两个对象之间是否已连接?
 * -# 如何记录对象间的连接关系?
 * 
 * 以集合的角度思考，可以认为连接在一起的对象属于同一个集合，
 * 进一步地说，对象组成的集合可以分为两种:
 * -# 含有复数个对象的集合，其内部的所有对象都互相连接，我们见这种集合称为"有连接集合"。
 * -# 只含有单个对象的集合，其内部的对象没有连接关系，我们将这种集合称为"无连接集合"。
 * 
 * 这样，判断两个对象之间是否已连接就是判断两个对象是否已经属于同一个集合，
 * 记录对象间的连接关系就是将两个对象纳入同一集合。
 * 
 * 再从计算机的角度思考，可以发现，上述关于集合的判断和记录，
 * 转换成计算机的操作就是:
 *  -# **搜索(find)** 含有指定对象的集合。
 *  -# 将代表新连接的对象对 **联合(union)** 到一个集合中。
 * 
 * 到此，我们实际上已经将一个实际问题抽象为数学问题，又将数学问题抽象到了计算机操作的层面，
 * 通过这样的抽象过程得到的计算机操作称为 **抽象操作(abstract operation)** 。
 * 
 * 获得抽象操作后，解决问题需要的算法和数据结构的轮廓就完全清楚了。
 * 对连接问题来说，算法和数据结构的基本目标就是实现搜索和联合两种操作。
 * 
 * 抽象在算法设计中是极为重要的，可以说是算法设计的根本方法。
 * 
 * ###状态分析(习题1.3)#
 * 
 * 得出抽象操作，就是确定了目标数据结构和算法的逻辑，
 * 有了逻辑，就能推导出我们将要实现的程序对各种输入的反应(即进入某种状态或提供某种输出)。
 * 
 * 解决连接问题的程序(简称为"连接程序")接受不同输入时，可能具有的状态如下:
 * | 搜索操作情况 | 联合操作情况 | 有连接集合的数量变化 |
 * | :--- | :--- | :---: |
 * | 输入的两个对象都不属于任何有连接集合 | 创建一个新有连接集合 | +1 |
 * | 输入的一个对象属于某个有连接集合，\n另一个对象属于无连接集合 | 把后一个对象纳入\n前一个对象所属的有连接集合 | 不变 |
 * | 输入的两个对象分别属于两个不同的有连接集合 | 把两个有连接集合合并成一个 | -1 |
 * | 输入的两个对象属于同一个有连接集合 | 不进任何操作 | 不变 |
 * 
 * ###示例流程#
 * 
 * 分析出状态后，就可以设计出一组能触发连接程序所有状态的输入，如下:
 * 
 * | 输入 | 状态 |
 * | :---: | :---: |
 * | 2-3 | 产生新有连接集合a |
 * | 5-7 | 产生新有连接集合b |
 * | 5-0 | 向有连接集合b添加新对象 |
 * | 0-3 | 合并有连接集合a, b |
 * | 7-3 | 连接已存在，无操作 |
 * 
 * 本文讨论算法的运行情况时，都会以本组输入作示例。
 * 
 * @{
 ****************************************/

/**
 * @brief 存储连接信息的数组的长度。
 * 
 * 数组的一个元素代表一个可被连接的对象。
 * 因此数组的长度决定了可被连接的对象的最大个数。
 */
#define N 10000

#ifndef DOC_COMPILE

int *qfind_new_storage(size_t object_num);
void qfind_delete_storage(int *storage);
bool qfind_is_new_connection(int *storage, size_t object_num, int p, int q);

int *qunion_new_storage(size_t object_num);
void qunion_delete_storage(int *storage);
bool qunion_is_new_connection(int *storage, int p, int q);

struct storage_with_tree_size {
    int *data, *tree_size;
};

struct storage_with_tree_size *w_qunion_new_storage(size_t object_num);
void w_qunion_delete_storage(struct storage_with_tree_size *storage);
bool w_qunion_is_new_connection(struct storage_with_tree_size *storage, int p, int q);

struct storage_with_tree_size *w_qunion_pc_new_storage(size_t object_num);
void w_qunion_pc_delete_storage(struct storage_with_tree_size *storage);
bool w_qunion_pc_is_new_connection(struct storage_with_tree_size *storage, int p, int q);

struct storage_with_tree_size *w_qunion_pc_h_new_storage(size_t object_num);
void w_qunion_pc_h_delete_storage(struct storage_with_tree_size *storage);
bool w_qunion_pc_h_is_new_connection(struct storage_with_tree_size *storage, int p, int q);

struct storage_with_tree_height {
    int *data, *tree_height;
};

struct storage_with_tree_height *h_qunion_new_storage(size_t object_num);
void h_qunion_delete_storage(struct storage_with_tree_height *storage);
bool h_qunion_is_new_connection(struct storage_with_tree_height *storage, int p, int q);

#endif // #ifndef DOC_COMPILE

/****************************************
 * @} -- Connectivity
 ****************************************/

#endif // HEADER_CONNECTIVITY_H