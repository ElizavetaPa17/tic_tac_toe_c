#include <stdio.h>

#include "constants.h"
#include "internal.h"
#include "draw.h"

int main(int argc, char *argv[]) {
    init_TTT();
    setup_TTT();

    draw_welcome_page();
    getch();
    clear();

    int symb = 0;

    post_menu(menu);
    refresh();

    while ((symb = getch()) != EOF) {
        switch (symb) {
            case KEY_UP: {
                menu_driver(menu, REQ_UP_ITEM);
                break;
            }
            case KEY_DOWN: {
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            }
            case KEY_RIGHT: {
                process_menu_choice();
                break;
            }
            case KEY_LEFT: {
                for (int i = 0; i < ITEM_COUNT; ++i) {
                    hide_panel(panels_array[i]);
                }

                break;
            }
        }

        clrtoeol();
    }

    quit_TTT();
}