#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>
#include "constants.h"
#include "internal.h"

char err_msg[BUFSIZ];

void panic(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void init_TTT() {
    if (!initscr() || start_color() == ERR) {
        snprintf(err_msg, sizeof(err_msg), "Failed to init %s environment\n", PROJECT_NAME);
        panic(err_msg);
    }
}

void setup_TTT() {
    if (raw() == ERR || cbreak() == ERR) { // disable buffering and control characters
        snprintf(err_msg, sizeof(err_msg), "Failed to setup %s: move the terminal into raw mode error\n", PROJECT_NAME);
        panic(err_msg);
    }

    init_pair(BACKGROUND_COLORS, COLOR_WHITE, COLOR_BLACK);
    init_pair(X_COLORS,          COLOR_RED,   COLOR_BLACK);
    init_pair(O_COLORS,          COLOR_GREEN, COLOR_BLACK);
}

void quit_TTT() {
    if (endwin() == ERR) {
        snprintf(err_msg, sizeof(err_msg), "Failed to quit %s: ncurses endwin error\n", PROJECT_NAME);
    }
}