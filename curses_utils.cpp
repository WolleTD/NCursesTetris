//
// Created by wolle on 25.08.19.
//

#include "Tetroid.h"
#include "math_utils.h"
#include <curses.h>

void printTetroid_impl(size_t y, size_t x, const Tetroid& tetroid, bool clear) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (tetroid.at(j, i) != ' ')
                mvaddch(y + i, x + j, (clear ? ' ' : tetroid.at(j, i)));
        }
    }
}

void printTetroid(pos position, const Tetroid& tetroid) {
    printTetroid_impl(position.y, position.x, tetroid, false);
}

void clearTetroid(pos position, const Tetroid& tetroid) {
    printTetroid_impl(position.y, position.x, tetroid, true);
}

void drawBox(pos pos1, pos pos2, char symbol) {
    size_t x1 = std::min(pos1.x, pos2.x);
    size_t x2 = std::max(pos1.x, pos2.x);
    size_t y1 = std::min(pos1.y, pos2.y);
    size_t y2 = std::max(pos1.y, pos2.y);
    mvaddstr(y1, x1, std::string(x2 - x1 + 1, symbol).c_str());
    mvaddstr(y2, x1, std::string(x2 - x1 + 1, symbol).c_str());
    for (size_t i = y1 + 1; i < y2; i++) {
        mvaddch(i, x1, symbol);
        mvaddch(i, x2, symbol);
    }
}