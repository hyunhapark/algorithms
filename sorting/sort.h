#ifndef SORT_H
#define SORT_H

#define INIT_SIZE        16
#define MODE_BUBBLE      1
#define MODE_INSERTION   2
#define MODE_SELECTION   3
#define MODE_QUICK       4
#define MODE_MERGE       5
#define MODE_HEAP        6

int *sort (int mode, int size, int *arr);

#endif
