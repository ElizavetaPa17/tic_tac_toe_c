#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>
#include "constants.h"
#include "internal.h"

void panic(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void init_TTT() {
    if (!initscr()) {
        char err_msg[64];
        snprintf(err_msg, sizeof(err_msg), "Failed to init %s", PROJECT_NAME);
        panic(err_msg);
    }
}