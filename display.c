/* display.c - screen output (plain text)
 * "\033[H" moves the cursor to the top-left so the board is redrawn in
 * place, "\033[K" clears the rest of the line.
 * The whole board takes H + 3 lines, so it fits a small terminal.
 * Syllabus: recursion (print_log), bubble sort (usage statistics),
 * list traversal (high scores) */
#include "common.h"
#include "display.h"
#include "sort.h"

void print_board(const Game *g, const HList *hs) {
    int r, c, pc, t;
    char cell[H][W];

    for (r = 0; r < H; r++)
        for (c = 0; c < W; c++)
            cell[r][c] = g->board[r][c] ? 'L' : ' ';      /* L = locked block */
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++)
            if (g->cur->m[r][c]) {
                int y = g->cur->y + r, x = g->cur->x + c;
                if (y >= 0 && y < H && x >= 0 && x < W) cell[y][x] = 'F';  /* falling */
            }

    t = cq_front(g->next);
    printf("\033[H  TETRIS  Score:%-5d Lvl:%-2d Lines:%-3d Best:%d\033[K\n",
           g->score, g->level, g->lines, hs->head ? hs->head->score : 0);
    printf("  +");
    for (c = 0; c < W; c++) printf("----");
    printf("+\033[K\n");
    for (r = 0; r < H; r++) {
        printf("  |");
        for (c = 0; c < W; c++) {
            if (cell[r][c] == 'L')      printf("[##]");    /* locked block  */
            else if (cell[r][c] == 'F') printf("[  ]");    /* falling block */
            else                        printf(" .  ");    /* empty         */
        }
        printf("|");
        switch (r) {
            case 0: printf("   NEXT PIECE"); break;
            case 1: case 2:                               /* only rows 0-1 of the 4x4 shape are used */
                printf("   ");
                for (pc = 0; pc < 4; pc++)
                    printf("%s", SHAPES[t][(r - 1) * 4 + pc] == 'X' ? "[  ]" : "    ");
                break;
            case 4: printf("   Left/Right : move"); break;
            case 5: printf("   Up         : rotate"); break;
            case 6: printf("   Down       : soft drop"); break;
            case 7: printf("   Space      : hard drop"); break;
            case 8: printf("   U          : undo"); break;
            case 9: printf("   Q          : quit"); break;
        }
        printf("\033[K\n");
    }
    printf("  +");
    for (c = 0; c < W; c++) printf("----");
    printf("+\033[K\n");
    fflush(stdout);
}

void show_summary(const Game *g, const HList *hs) {
    Stat st[7];
    const LNode *n;
    const HNode *h;
    int i, rank = 1;

    printf("\033[J\n  ===== GAME OVER =====\n  Score: %d   Lines: %d\n", g->score, g->lines);

    printf("  Pieces placed (%d): ", g->log.size);
    print_log(g->log.head);                              /* recursion */
    printf("\n");

    for (i = 0; i < 7; i++) { st[i].type = i; st[i].count = 0; }
    for (n = g->log.head; n != NULL; n = n->next) st[n->type].count++;
    bubble_sort_desc(st, 7);                             /* sort by count */
    printf("  Most used pieces: ");
    for (i = 0; i < 7; i++) printf("%c=%d ", LETTERS[st[i].type], st[i].count);
    printf("\n");

    printf("  --- High scores ---\n");
    for (h = hs->head; h != NULL; h = h->next, rank++)   /* traverse */
        printf("  %d. %-8d (%d lines)\n", rank, h->score, h->lines);
    fflush(stdout);
}