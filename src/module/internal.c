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

    for (int i = 0; i < ITEM_COUNT; ++i) {
        hide_panel(panels_array[i]);
    }

    void (*panel_func)(void);
    if (curr_item == menu_items_array[0]) { // PLAY GAME
        show_panel(panels_array[0]);
        panel_func = panel_userptr(panels_array[0]);
    } else if (curr_item == menu_items_array[1]) { // DISPLAY_STATISTICS
        show_panel(panels_array[1]);
        panel_func = panel_userptr(panels_array[1]);
    } else {
        panel_func = panel_userptr(panels_array[2]);
    }

    panel_func();

    update_panels();
    doupdate();
}

void start_game() {
    clear();
    char players_name[2][PLAYER_NAME_LENGTH];

    for (int i = 0, result = 0; i < 2; ++i) {
        move(LINES-2, 0);
        clrtoeol();
        printw("Player #%d, choose your name (less than 100 symbols): ", i);

        while (True) {
            result = getnstr(players_name[i], PLAYER_NAME_LENGTH);
            switch (result) {
                case ERR:
                    mvprintw(LINES-2, 0, "Enter correct name less than 100 symbols!");
                    continue;
                case KEY_RESIZE: // resize window
                    continue;
                case OK:
                    goto success_name_input;                    
            }
        }

    success_name_input:
        clrtoeol();
        continue;
    }

    mvprintw(LINES-2, 0, "%s and %s, let's start our game! Enter when you become ready!", players_name[0], players_name[1]);
    clear();

    mvprintw(LINES-3, 0, "%s, you will use tic!", players_name[0]);
    mvprintw(LINES-2, 0, "%s, you will use tac-toe!", players_name[1]);
    getch();

    clear();

    for (int i = 1; ; ++i) {
        if (i & 1) { // the first player attempt
            mvprintw(LINES-2, 0, "%s, this is your turn!", players_name[0]);
        } else { // the second player attempt
            mvprintw(LINES-2, 0, "%s, this is your turn!", players_name[1]);
        }
    }
}

void display_statistics() {
    clean_information();

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
        windows_array[i] = newwin(LINES/1.5, COLS/2, 5, 5);
    }
}