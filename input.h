/* input.h - keyboard and timer (platform layer) */
#ifndef INPUT_H
#define INPUT_H

enum { K_NONE, K_LEFT, K_RIGHT, K_DOWN, K_ROT, K_DROP, K_UNDO, K_QUIT, K_RESTART };

void term_init(void);        /* switch terminal to instant-key mode   */
void term_restore(void);     /* put the terminal back                 */
int  get_key(void);          /* returns a K_ value, K_NONE if no key  */
long now_ms(void);           /* milliseconds, used for gravity        */
void sleep_ms(int ms);

#endif