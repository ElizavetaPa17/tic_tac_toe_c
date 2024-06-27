#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include <time.h>

#define PROJECT_NAME "Panteriza's Tic-Tac-Toe"

extern const char description[];

#define BACKGROUND_COLORS 1
#define X_COLORS 2
#define O_COLORS 3

#define LABEL_WIDTH 33
#define LABEL_HEIGHT 8
#define BOARD_WIDTH 16
#define BOARD_X_OFFET 11
#define BOARD_Y_OFFSET 8

#define PLAYER_NAME_LENGTH 100

#define ENTER_CODE 10

enum {
    False, 
    True
};

extern struct timespec displaying_delay;

#define ITEM_COUNT 3
extern const char* item_names[ITEM_COUNT];

extern ITEM** menu_items_array;
extern MENU*  menu;

extern WINDOW* windows_array[ITEM_COUNT];
extern PANEL*  panels_array[ITEM_COUNT];

extern char board[3][3];

#endif