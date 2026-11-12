/* piece.c - shapes and rotation
 * Syllabus: Multidimensional arrays, address calculation (r*4 + c) */
#include "common.h"
#include "piece.h"

const char *SHAPES[7] = {
    "....XXXX........",  /* I */
    ".XX..XX.........",  /* O */
    ".X..XXX.........",  /* T */
    ".XX.XX..........",  /* S */
    "XX...XX.........",  /* Z */
    "X...XXX.........",  /* J */
    "..X.XXX........."   /* L */
};
const char LETTERS[8] = "IOTSZJL";

void piece_load(Piece *p, int type) {
    int r, c;
    p->type = type;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++)
            p->m[r][c] = (SHAPES[type][r * 4 + c] == 'X');
}

/* Rotate clockwise: new[c][n-1-r] = old[r][c].  O(n^2) */
void piece_rotate(Piece *p) {
    int tmp[4][4], r, c, n;
    if (p->type == 1) return;             /* O piece looks the same */
    n = (p->type == 0) ? 4 : 3;
    memset(tmp, 0, sizeof tmp);
    for (r = 0; r < n; r++)
        for (c = 0; c < n; c++)
            tmp[c][n - 1 - r] = p->m[r][c];
    memcpy(p->m, tmp, sizeof tmp);
}