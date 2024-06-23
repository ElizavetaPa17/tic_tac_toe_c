#include "constants.h"

const char description[] = "Panteriza's Tic-Tac-Toe.";

struct timespec displaying_delay = {1, 0};

const char* item_names[ITEM_COUNT] = {
    "Play",
    "Statistics",
    "Exit"
};

ITEM** menu_items_array = NULL;
MENU*  menu = NULL;

WINDOW* windows_array[ITEM_COUNT];
PANEL*  panels_array[ITEM_COUNT];