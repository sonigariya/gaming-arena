# Tetris in C (Data Structures project)

Tetris game written in C using only the standard library. No external libraries and no file I/O.

## Build and run

```
gcc *.c -o tetris
./tetris
```

On Windows use `gcc *.c -o tetris.exe` and run `tetris.exe` in Windows Terminal, PowerShell or the VS Code terminal.

## Controls

| Key | Action |
|---|---|
| Left / Right arrow (or A / D) | Move |
| Up arrow (or W) | Rotate |
| Down arrow (or S) | Soft drop |
| Space | Hard drop |
| U | Undo |
| Q | Quit |
| R | Play again (after game over) |

## Files

| File | Purpose | Data structure / topic |
|---|---|---|
| `common.h` | Shared constants (board size, capacities) and `xcalloc` | Dynamic memory allocation |
| `piece.c / piece.h` | Piece shapes, loading, rotation | 2D array, address calculation |
| `queue.c / queue.h` | Upcoming pieces | Circular queue |
| `stack.c / stack.h` | Undo history, rows waiting to be cleared | Array stack and linked stack |
| `list.c / list.h` | Piece log, high-score table | Singly and doubly linked list, recursion |
| `sort.c / sort.h` | Random piece order, usage statistics | Insertion sort, bubble sort |
| `game.c / game.h` | Board, collisions, line clearing, gravity | 2D array, recursion, tail recursion |
| `display.c / display.h` | Draws the board and the game-over screen | |
| `input.c / input.h` | Keyboard and timer | Platform layer (not a syllabus topic) |
| `main.c` | Game loop | |

`input.c` is the only file that is not plain C and data structures. Reading a key without pressing Enter needs `termios` (Linux/Mac) or `conio.h` (Windows).