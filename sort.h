/* sort.h - sorting algorithms */
#ifndef SORT_H
#define SORT_H

typedef struct { int type; int key; } BagItem;    /* piece + random key  */
typedef struct { int type; int count; } Stat;     /* piece + times used  */

void insertion_sort(BagItem a[], int n);          /* ascending by key    */
void bubble_sort_desc(Stat a[], int n);           /* descending by count */

#endif