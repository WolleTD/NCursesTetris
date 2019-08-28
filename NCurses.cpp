//
// Created by wolle on 25.08.19.
//

#include "NCurses.h"
#include <curses.h>
#include <algorithm>
#include <cstddef>
#include <string>

void NCurses::drawBox(position pos1, position pos2, char symbol) {
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