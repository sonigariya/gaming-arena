/* game.c - game rules
 * Syllabus used here:
 *   Unit 1  pointers, structures, malloc/free, 2D array (board),
 *           linked stack (rows to clear), recursion, tail recursion
 *   Unit 2  circular queue (next pieces), singly linked list (piece log)
 *   Unit 4  insertion sort (random 7-bag) */
#include "commonn.h"
#include "gamme.h"
#include "sort.h"

/* ---------------- 7-bag: shuffle by sorting on a random key ---------------- */
static void bag_refill(Game *g) {
    BagItem items[7];
    int i;
    for (i = 0; i < 7; i++) { items[i].type = i; items[i].key = rand(); }
    insertion_sort(items, 7);
    for (i = 0; i < 7; i++) g->bag[i] = items[i].type;
    g->bag_idx = 0;
}

static int bag_next(Game *g) {
    if (g->bag_idx >= 7) bag_refill(g);
    return g->bag[g->bag_idx++];
}

static void fill_queue(Game *g) {
    while (!cq_is_full(g->next)) cq_add(g->next, bag_next(g));
}

/* ---------------- create / destroy (dynamic memory) ---------------- */
Game *game_create(void) {
    Game *g = xcalloc(1, sizeof *g);
    int r;
    g->board = xcalloc(H, sizeof(int *));
    for (r = 0; r < H; r++) g->board[r] = xcalloc(W, sizeof(int));
    g->cur = xcalloc(1, sizeof(Piece));
    g->next = cq_create(QCAP);
    as_init(&g->undo);
    ll_init(&g->log);
    g->level = 1;
    bag_refill(g);
    fill_queue(g);
    return g;
}

void game_destroy(Game *g) {
    int r;
    for (r = 0; r < H; r++) free(g->board[r]);
    free(g->board);
    free(g->cur);
    cq_destroy(g->next);
    ll_free(&g->log);
    free(g);
}

/* ---------------- movement ---------------- */
static int collides(const Game *g, const Piece *p) {
    int r, c, bx, by;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++) {
            if (!p->m[r][c]) continue;
            bx = p->x + c;
            by = p->y + r;
            if (bx < 0 || bx >= W || by >= H) return 1;
            if (by >= 0 && g->board[by][bx]) return 1;
        }
    return 0;
}

int game_move(Game *g, int dx, int dy) {
    Piece t = *g->cur;
    t.x += dx;
    t.y += dy;
    if (collides(g, &t)) return 0;
    *g->cur = t;
    return 1;
}

void game_rotate(Game *g) {
    static const int kicks[5] = {0, -1, 1, -2, 2};   /* shift sideways if blocked */
    Piece t;
    int i;
    for (i = 0; i < 5; i++) {
        t = *g->cur;
        piece_rotate(&t);
        t.x += kicks[i];
        if (!collides(g, &t)) { *g->cur = t; return; }
    }
}

void game_spawn(Game *g) {
    int type = cq_delete(g->next);        /* delete from the queue */
    fill_queue(g);                        /* add at the rear */
    piece_load(g->cur, type);
    g->cur->x = (W - 4) / 2;              /* centre the 4x4 box */
    g->cur->y = 0;
    if (collides(g, g->cur)) g->over = 1;
}

/* ---------------- clearing rows ---------------- */

/* RECURSION: move every row above r down by one. Time O(r*W), depth r. */
static void shift_rows_down(Game *g, int r) {
    if (r == 0) {                         /* base case */
        memset(g->board[0], 0, W * sizeof(int));
        return;
    }
    memcpy(g->board[r], g->board[r - 1], W * sizeof(int));
    shift_rows_down(g, r - 1);
}

/* Linked STACK: scan bottom -> top pushing full rows; the top-most full row
 * is popped first, so rows still waiting below it keep valid indices. */
static int clear_lines(Game *g) {
    static const int pts[5] = {0, 100, 300, 500, 800};
    LStack st;
    int r, c, full, cleared = 0;

    ls_init(&st);
    for (r = H - 1; r >= 0; r--) {
        full = 1;
        for (c = 0; c < W; c++)
            if (!g->board[r][c]) { full = 0; break; }
        if (full) ls_push(&st, r);
    }
    while (!ls_is_empty(&st)) {
        r = ls_pop(&st);
        shift_rows_down(g, r);
        cleared++;
    }
    if (cleared) {
        g->score += pts[cleared] * g->level;
        g->lines += cleared;
        g->level = g->lines / 10 + 1;
    }
    return cleared;
}

void game_lock(Game *g) {
    int r, c, cleared;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++)
            if (g->cur->m[r][c] && g->cur->y + r >= 0)
                g->board[g->cur->y + r][g->cur->x + c] = g->cur->type + 1;
    cleared = clear_lines(g);
    ll_append(&g->log, g->cur->type, cleared);   /* singly linked list */
    as_init(&g->undo);                           /* cannot undo past a lock */
    game_spawn(g);
}

/* TAIL RECURSION: keep moving down until blocked; 'dist' is the accumulator */
static int drop_rec(Game *g, int dist) {
    if (!game_move(g, 0, 1)) return dist;
    return drop_rec(g, dist + 1);
}

void game_hard_drop(Game *g) {
    int d = drop_rec(g, 0);
    g->score += 2 * d;
    game_lock(g);
}

int game_fall_delay_ms(const Game *g) {
    int d = 800 - (g->level - 1) * 70;       /* faster at higher levels */
    return d < 100 ? 100 : d;
}
