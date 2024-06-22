#include <ncurses.h>
#include <time.h>

#include "constants.h"

void clear_screen() {
    clear();
}

#define LABEL_WIDTH 33
#define LABEL_HEIGHT 8
#define BOARD_WIDTH 16
#define BOARD_X_OFFET 11
#define BOARD_Y_OFFSET 8

struct timespec displaying_delay = { 1, 0 };

/* 
// Labels to draw

    <===============================>
    0        1         2         3
    123456789012345678901234567890123

    ┌─────┬─────┐     ┬      ┌───────┐   + 1
          │           │      │           | 2
          │           │      │           | 3
          │           │      │           | 4
          │           │      │           | 5
          │           │      │           | 6
          ┴           ┴      └───────┘   + 7

    ┌─────┬─────┐ ┌───────┐  ┌───────┐
          │       │       │  │        
          │       │       │  │    
          │       │───────│  │     
          │       │       │  │      
          │       |       |  │      
          ┴       ┴       ┴  └───────┘

    ┌─────┬─────┐ ┌───────┐  ┌───────┐
          │       |       |  │        
          │       |       |  │      
          │       |       |  ├───────┤       
          │       |       |  │      
          │       |       |  │      
          ┴       └───────┘  └───────┘

// Draw Tic-Tac-Toe board
    <==============>
    0        1
    1234567890123456
    ┌────┬────┬────┐
    │    │    │    │
    ├────┼────┼────┤
    │    │    │    │
    ├────┼────┼────┤
    │    │    │    │
    └────┴────┴────┘
*/

void draw_T(int ul_x, int ul_y);
void draw_I(int ul_x, int ul_y);
void draw_C(int ul_x, int ul_y);
void draw_A(int ul_x, int ul_y);
void draw_O(int ul_x, int ul_y);
void draw_E(int ul_x, int ul_y);

void draw_board(int ul_x, int ul_y);
void draw_first_step(int ul_x, int ul_y);
void draw_second_step(int ul_x, int ul_y);
void draw_third_step(int ul_x, int ul_y);

void draw_welcome_page() {
    int  max_col = 0,
         max_row = 0;
    getmaxyx(stdscr, max_row, max_col);
    
    int x = 0,
        y = 0;
    x = ((max_col - LABEL_WIDTH) >> 1);
    y = ((max_row - LABEL_HEIGHT) >> 1) - 10;

    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;

    attron(COLOR_PAIR(BACKGROUND_COLORS));
    // draw "TIC"
    draw_T(x, y);
    draw_I(x+18, y);
    draw_C(x+25, y);
    draw_board(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);
    draw_first_step(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);

    refresh();
    nanosleep(&displaying_delay, NULL);
    clear();

    // draw "TAC"
    draw_T(x, y);
    draw_A(x+14, y);
    draw_C(x+25, y);
    draw_board(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);
    draw_second_step(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);

    refresh();
    nanosleep(&displaying_delay, NULL);
    clear();

    // draw "TOE"
    draw_T(x, y);
    draw_O(x+14, y);
    draw_E(x+25, y);
    draw_board(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);
    draw_third_step(x+BOARD_X_OFFET, y+BOARD_Y_OFFSET);

    refresh();
    nanosleep(&displaying_delay, NULL);
}

/*
 Draw T starting from ul_x (upper left x) and ul_y (upper left y)
*/
void draw_T(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+12, ACS_URCORNER);
    mvaddch(ul_y,    ul_x+6,  ACS_TTEE);
    mvaddch(ul_y+6,  ul_x+6,  ACS_BTEE);

    for (int i = 1, offset = 6; i <= 5; ++i) {
        mvaddch(ul_y,   ul_x+i,        ACS_HLINE);
        mvaddch(ul_y,   ul_x+offset+i, ACS_HLINE);
        mvaddch(ul_y+i, ul_x+offset,   ACS_VLINE);
    }
}

/*
 Draw I like draw_T function.
*/
void draw_I(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,  ACS_TTEE);
    mvaddch(ul_y+6,  ul_x,  ACS_BTEE);

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x, ACS_VLINE);
    }
}

/*
 Draw C like draw_T function.
*/
void draw_C(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+8,  ACS_URCORNER);
    mvaddch(ul_y+6,  ul_x,    ACS_LLCORNER);
    mvaddch(ul_y+6,  ul_x+8,  ACS_LRCORNER);

    for (int i = 1; i <= 7; ++i) {
        mvaddch(ul_y,   ul_x+i, ACS_HLINE);
        mvaddch(ul_y+6, ul_x+i, ACS_HLINE);
    }

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x, ACS_VLINE);
    }
}

/*
 Draw A like draw_T function.
*/
void draw_A(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+8,  ACS_URCORNER);
    mvaddch(ul_y+6,  ul_x,    ACS_BTEE);
    mvaddch(ul_y+6,  ul_x+8,  ACS_BTEE);

    for (int i = 1; i <= 7; ++i) {
        mvaddch(ul_y,   ul_x+i, ACS_HLINE);
        mvaddch(ul_y+3, ul_x+i, ACS_HLINE);
    }

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x,   ACS_VLINE);
        mvaddch(ul_y+i, ul_x+8, ACS_VLINE);
    }
}

/*
 Draw O like draw_T function.
*/
void draw_O(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+8,  ACS_URCORNER);
    mvaddch(ul_y+6,  ul_x,    ACS_LLCORNER);
    mvaddch(ul_y+6,  ul_x+8,  ACS_LRCORNER);

    for (int i = 1; i <= 7; ++i) {
        mvaddch(ul_y,   ul_x+i, ACS_HLINE);
        mvaddch(ul_y+6, ul_x+i, ACS_HLINE);
    }

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x,   ACS_VLINE);
        mvaddch(ul_y+i, ul_x+8, ACS_VLINE);
    }
}

/*
 Draw E like draw_T function.
*/
void draw_E(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+8,  ACS_URCORNER);
    mvaddch(ul_y+3,  ul_x+4,  ACS_RTEE);
    mvaddch(ul_y+6,  ul_x,    ACS_LLCORNER);
    mvaddch(ul_y+6,  ul_x+8,  ACS_LRCORNER);

    for (int i = 1; i <= 7; ++i) {
        mvaddch(ul_y,   ul_x+i, ACS_HLINE);
        mvaddch(ul_y+3, ul_x+i, ACS_HLINE);
        mvaddch(ul_y+6, ul_x+i, ACS_HLINE);
    }

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x, ACS_VLINE);
    }
}

/*
    Draw board like draw_T function.
    ┌────┬────┬────┐
    │    │    │    │
    ├────┼────┼────┤
    │    │    │    │
    ├────┼────┼────┤
    │    │    │    │
    └────┴────┴────┘
*/
void draw_board(int ul_x, int ul_y) {
    mvaddch(ul_y,    ul_x,    ACS_ULCORNER);
    mvaddch(ul_y,    ul_x+15, ACS_URCORNER);
    mvaddch(ul_y+6,  ul_x,    ACS_LLCORNER);
    mvaddch(ul_y+6,  ul_x+15, ACS_LRCORNER);

    for (int i = 1; i <= 14; ++i) {
        mvaddch(ul_y,   ul_x+i, ACS_HLINE);
        mvaddch(ul_y+2, ul_x+i, ACS_HLINE);
        mvaddch(ul_y+4, ul_x+i, ACS_HLINE);
        mvaddch(ul_y+6, ul_x+i, ACS_HLINE);
    }

    for (int i = 1; i <= 5; ++i) {
        mvaddch(ul_y+i, ul_x,    ACS_VLINE);
        mvaddch(ul_y+i, ul_x+5,  ACS_VLINE);
        mvaddch(ul_y+i, ul_x+10, ACS_VLINE);
        mvaddch(ul_y+i, ul_x+15, ACS_VLINE);
    }

    for (int i = 1; i <= 2; ++i) {
        mvaddch(ul_y,     ul_x+i*5, ACS_TTEE);
        mvaddch(ul_y+6,   ul_x+i*5, ACS_BTEE);

        mvaddch(ul_y+i*2, ul_x,    ACS_LTEE);
        mvaddch(ul_y+i*2, ul_x+15, ACS_RTEE);

        mvaddch(ul_y+i*2, ul_x+5, ACS_PLUS);
        mvaddch(ul_y+i*2, ul_x+10, ACS_PLUS);
    }
}

/*
 Draw the first step in Tic-Tac-Toe board.
    ┌────┬────┬────┐
    │  X │    │    │
    ├────┼────┼────┤
    │    │  O │    │
    ├────┼────┼────┤
    │    │    │    │
    └────┴────┴────┘
*/
void draw_first_step(int ul_x, int ul_y) {
    attron(COLOR_PAIR(X_COLORS));
    mvaddch(ul_y+1, ul_x+3, 'X');
    attroff(COLOR_PAIR(X_COLORS));

    attron(COLOR_PAIR(O_COLORS));
    mvaddch(ul_y+3, ul_x+8, 'O');
    attroff(COLOR_PAIR(O_COLORS));
}

/*
 Draw the second step in Tic-Tac-Toe board.
    ┌────┬────┬────┐
    │  x │    │  X │
    ├────┼────┼────┤
    │    │  o │    │
    ├────┼────┼────┤
    │  O │    │    │
    └────┴────┴────┘
*/
void draw_second_step(int ul_x, int ul_y) {
    draw_first_step(ul_x, ul_y);

    attron(COLOR_PAIR(X_COLORS));
    mvaddch(ul_y+1, ul_x+13, 'X');
    attroff(COLOR_PAIR(X_COLORS));

    attron(COLOR_PAIR(O_COLORS));
    mvaddch(ul_y+5, ul_x+3, 'O');
    attroff(COLOR_PAIR(O_COLORS));
}

/*
 Draw the third step in Tic-Tac-Toe board.
    ┌────┬────┬────┐
    │  x │  O │  x │
    ├────┼────┼────┤
    │    │  o │    │
    ├────┼────┼────┤
    │  o │    │  X │
    └────┴────┴────┘
*/
void draw_third_step(int ul_x, int ul_y) {
    draw_second_step(ul_x, ul_y);

    attron(COLOR_PAIR(X_COLORS));
    mvaddch(ul_y+5, ul_x+13, 'X');
    attroff(COLOR_PAIR(X_COLORS));

    attron(COLOR_PAIR(O_COLORS));
    mvaddch(ul_y+1, ul_x+8, 'O');
    attroff(COLOR_PAIR(O_COLORS));
}