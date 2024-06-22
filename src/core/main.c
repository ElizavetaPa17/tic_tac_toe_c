#include <stdio.h>

#include "internal.h"
#include "draw.h"

int main(int argc, char *argv[]) {
    init_TTT();
    setup_TTT();

    draw_welcome_page();
    getch();

    quit_TTT();
}