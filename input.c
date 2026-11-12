/* input.c - PLATFORM LAYER (not a syllabus topic)
 *
 * Reading a key without pressing Enter and measuring time need operating
 * system functions (termios on Linux/Mac, conio.h on Windows). Everything
 * else in the project is plain C and data structures.
 *
 * Arrow keys send more than one byte:
 *   Linux/Mac : ESC [ A / B / C / D   (27, 91, 65..68)
 *   Windows   : 224 then 72 / 80 / 75 / 77 */
#include <stdio.h>
#include "input.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

void term_init(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | 0x0004);
    printf("\033[2J\033[?25l");
}
void term_restore(void) { printf("\033[?25h"); }
long now_ms(void) { return (long)GetTickCount(); }
void sleep_ms(int ms) { Sleep(ms); }

int get_key(void) {
    int c;
    if (!_kbhit()) return K_NONE;
    c = _getch();
    if (c == 0 || c == 224) {                   /* arrow keys */
        c = _getch();
        switch (c) {
            case 72: return K_ROT;
            case 80: return K_DOWN;
            case 75: return K_LEFT;
            case 77: return K_RIGHT;
        }
        return K_NONE;
    }
    switch (c) {
        case 'a': case 'A': return K_LEFT;
        case 'd': case 'D': return K_RIGHT;
        case 's': case 'S': return K_DOWN;
        case 'w': case 'W': return K_ROT;
        case ' ': return K_DROP;
        case 'u': case 'U': return K_UNDO;
        case 'q': case 'Q': return K_QUIT;
        case 'r': case 'R': return K_RESTART;
    }
    return K_NONE;
}

#else
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>

static struct termios old_term;

void term_init(void) {
    struct termios t;
    tcgetattr(0, &old_term);
    t = old_term;
    t.c_lflag &= ~(ICANON | ECHO);              /* no Enter, no echo */
    t.c_cc[VMIN] = 0;                           /* do not wait for a key */
    t.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &t);
    printf("\033[2J\033[?25l");
}
void term_restore(void) {
    tcsetattr(0, TCSANOW, &old_term);
    printf("\033[?25h");
}
long now_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000;
}
void sleep_ms(int ms) { usleep(ms * 1000); }

int get_key(void) {
    unsigned char c, s0, s1;
    if (read(0, &c, 1) != 1) return K_NONE;
    if (c == 27) {                              /* arrow keys: ESC [ A/B/C/D */
        if (read(0, &s0, 1) == 1 && read(0, &s1, 1) == 1 && s0 == '[') {
            switch (s1) {
                case 'A': return K_ROT;
                case 'B': return K_DOWN;
                case 'C': return K_RIGHT;
                case 'D': return K_LEFT;
            }
        }
        return K_NONE;
    }
    switch (c) {
        case 'a': case 'A': return K_LEFT;
        case 'd': case 'D': return K_RIGHT;
        case 's': case 'S': return K_DOWN;
        case 'w': case 'W': return K_ROT;
        case ' ': return K_DROP;
        case 'u': case 'U': return K_UNDO;
        case 'q': case 'Q': return K_QUIT;
        case 'r': case 'R': return K_RESTART;
    }
    return K_NONE;
}
#endif