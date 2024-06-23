#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "internal.h"

char err_msg[BUFSIZ];

void panic(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void setup_menu();
void setup_pannels();
void setup_windows();

void start_game();
void display_statistics();

void init_TTT() {
    if (!initscr() || start_color() == ERR || keypad(stdscr, TRUE) == ERR) {
        snprintf(err_msg, sizeof(err_msg), "Failed to init %s environment\n", PROJECT_NAME);
        panic(err_msg);
    }
}

void setup_TTT() {
    if (raw() == ERR || cbreak() == ERR) { // disable buffering and control characters
        snprintf(err_msg, sizeof(err_msg), "Failed to setup %s: move the terminal into necessary mode error\n", PROJECT_NAME);
        panic(err_msg);
    }

    init_pair(BACKGROUND_COLORS, COLOR_WHITE, COLOR_BLACK);
    init_pair(X_COLORS,          COLOR_RED,   COLOR_BLACK);
    init_pair(O_COLORS,          COLOR_GREEN, COLOR_BLACK);

    setup_menu();
    setup_windows();
    setup_pannels();
}

void quit_TTT() {
    for (int i = 0; i < ITEM_COUNT; ++i) {
        free_item(menu_items_array[i]);
    }
    free_menu(menu);

    if (endwin() == ERR) {
        snprintf(err_msg, sizeof(err_msg), "Failed to quit %s: ncurses endwin error\n", PROJECT_NAME);
    }

    exit(EXIT_SUCCESS);
}

void process_menu_choice() {
    ITEM* curr_item = current_item(menu);

    void (*panel_func)(void);
    if (curr_item == menu_items_array[0]) { // PLAY GAME
        show_panel(panels_array[0]);
        panel_func = panel_userptr(panels_array[0]);
    } else if (curr_item == menu_items_array[1]) { // DISPLAY_STATISTICS
        show_panel(panels_array[1]);
        panel_func = panel_userptr(panels_array[1]);
    } else {
        show_panel(panels_array[2]);
        panel_func = panel_userptr(panels_array[2]);
    }

    panel_func();
}

void start_game() {
    mvprintw(LINES-2, 0, "Start Game!");
}

void display_statistics() {
    mvprintw(LINES-2, 0, "Display Statistics!");
}

void setup_menu() {
    menu_items_array = (ITEM**)calloc(ITEM_COUNT+1, sizeof(ITEM*));
    for (int i = 0; i < ITEM_COUNT; ++i) {
        menu_items_array[i] = new_item(item_names[i], NULL);
    }

    menu_items_array[ITEM_COUNT] = (ITEM*)NULL;
    menu = new_menu((ITEM**)menu_items_array);
}

void setup_pannels() {
    for (int i = 0; i < ITEM_COUNT; ++i) {
        panels_array[i] = new_panel(windows_array[i]);
        hide_panel(panels_array[i]);
    }

    set_panel_userptr(panels_array[0], start_game);
    set_panel_userptr(panels_array[1], display_statistics);
    set_panel_userptr(panels_array[2], quit_TTT);
}

void setup_windows() {
    for (int i  = 0; i < ITEM_COUNT; ++i) {
        windows_array[i] = newwin(100, 100, 5, 5);
    }
}