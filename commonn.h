/* common.h - constants and helpers shared by every module */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 8              /* board width  */
#define H 16             /* board height */
#define QCAP 4           /* circular queue capacity */
#define UCAP 25          /* undo stack capacity */
#define MAX_SCORES 5     /* entries kept in the high-score list */

/* calloc that stops the program if memory is not available */
static inline void *xcalloc(size_t n, size_t size) {
    void *p = calloc(n, size);
    if (p == NULL) { printf("Out of memory\n"); exit(1); }
    return p;
}

#endif
