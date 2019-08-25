//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_CURSES_UTILS_H
#define NCURSESTETRIS_CURSES_UTILS_H

#include "Tetroid.h"

void printTetroid_impl(size_t y, size_t x, const Tetroid& tetroid, bool clear);

void printTetroid(pos position, const Tetroid& tetroid);

void clearTetroid(pos position, const Tetroid& tetroid);

void drawBox(pos pos1, pos pos2, char symbol);

#endif //NCURSESTETRIS_CURSES_UTILS_H
