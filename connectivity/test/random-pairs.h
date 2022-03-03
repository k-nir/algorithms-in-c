#ifndef HEADER_RANDOM_PAIRS_H
#define HEADER_RANDOM_PAIRS_H

struct random_pairs {
    int (*pairs)[2];
};

struct random_pairs *random_pairs_new(int object_num, int pair_num);
void random_pairs_delete(struct random_pairs *pairs);

#endif // HEADER_RANDOM_PAIRS_H
