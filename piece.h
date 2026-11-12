/* piece.h - the falling block (structure + 2D array) */
#ifndef PIECE_H
#define PIECE_H

typedef struct {
    int type;        /* 0..6 = I O T S Z J L */
    int x, y;        /* top-left of the 4x4 matrix on the board */
    int m[4][4];     /* current shape, 1 = filled */
} Piece;

extern const char *SHAPES[7];   /* 4x4 matrices stored row-major */
extern const char LETTERS[8];   /* "IOTSZJL" */

void piece_load(Piece *p, int type);
void piece_rotate(Piece *p);

#endif