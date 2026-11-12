/* sort.c - sorting
 * Syllabus (Unit 4): insertion sort, bubble sort, sorting on different keys */
#include "sort.h"

/* Insertion sort on the 'key' field. O(n^2), n = 7.
 * Used for the random 7-bag: random keys give a random order of pieces. */
void insertion_sort(BagItem a[], int n) {
    int i, j;
    BagItem tmp;
    for (i = 1; i < n; i++) {
        tmp = a[i];
        j = i - 1;
        while (j >= 0 && a[j].key > tmp.key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = tmp;
    }
}

/* Bubble sort (descending) on the 'count' field. O(n^2), n = 7.
 * Used for the "most used pieces" statistics on the game-over screen. */
void bubble_sort_desc(Stat a[], int n) {
    int i, j;
    Stat tmp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (a[j].count < a[j + 1].count) {
                tmp = a[j]; a[j] = a[j + 1]; a[j + 1] = tmp;
            }
}