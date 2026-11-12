/* main.c - game loop
 * Real time: read keys, move the piece, apply gravity, redraw. */
#include<stdio.h>
#include <time.h>
#include "commonn.h"
#include "gamme.h"
#include "list.h"
#include "input.h"
#include "display.h"

/* One full game. Returns 1 if the player pressed Q. */
static int play(Game *g, const HList *hs) {
    long last_fall;
    int key, dirty;
    Piece prev;

    game_spawn(g);
    last_fall = now_ms();
    print_board(g, hs);

    while (!g->over) {
        dirty = 0;
        while ((key = get_key()) != K_NONE) {
            if (key == K_QUIT) return 1;
            if (key == K_RESTART) continue;

            if (key == K_UNDO) {                         /* pop from array stack */
                if (as_pop(&g->undo, &prev)) *g->cur = prev;
                dirty = 1;
                continue;
            }

            as_push(&g->undo, g->cur);                   /* push current state */
            switch (key) {
                case K_LEFT:  game_move(g, -1, 0); break;
                case K_RIGHT: game_move(g, 1, 0);  break;
                case K_DOWN:  game_move(g, 0, 1);  break;
                case K_ROT:   game_rotate(g);      break;
                case K_DROP:  game_hard_drop(g); last_fall = now_ms(); break;
            }
            dirty = 1;
            if (g->over) break;
        }

        if (!g->over && now_ms() - last_fall >= game_fall_delay_ms(g)) {   /* gravity */
            if (!game_move(g, 0, 1)) game_lock(g);
            last_fall = now_ms();
            dirty = 1;
        }

        if (dirty) print_board(g, hs);
        sleep_ms(10);
    }
    return 0;
}

void playtetris() {
    HList scores;
    Game *g;
    int quit = 0, key, decided;

    srand((unsigned)time(NULL));
    hl_init(&scores);
    term_init();

    while (!quit) {
        g = game_create();
        quit = play(g, &scores);
        hl_insert(&scores, g->score, g->lines);          /* doubly linked list */

        print_board(g, &scores);
        show_summary(g, &scores);

        if (!quit) {
            printf("\n  Press R to play again, Q to quit\n");
            fflush(stdout);
            decided = 0;
            while (!decided) {
                while ((key = get_key()) != K_NONE) {    /* drain pending keys */
                    if (key == K_RESTART) { decided = 1; break; }
                    if (key == K_QUIT) { quit = 1; decided = 1; break; }
                }
                if (!decided) sleep_ms(30);
            }
            printf("\033[2J");
        }
        game_destroy(g);
    }

    term_restore();
    hl_free(&scores);
    printf("\n  Thanks for playing!\n");
    return ;
}
