#ifndef INTERNAL_H
#define INTERNAL_H

#include <ncurses.h>

void panic(const char *msg);

void init_TTT();

void setup_TTT();

void quit_TTT();

#endif