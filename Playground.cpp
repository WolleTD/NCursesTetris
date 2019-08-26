//
// Created by wolle on 25.08.19.
//

#include <curses.h>
#include "NCurses.h"
#include "Playground.h"
#include "Tetroid.h"


bool Playground::collision(const position& pos, const Tetroid& tetroid) const {
    for (size_t x = 0; x < 4; x++) {
        for (size_t y = 0; y < 4; y++) {
            if ((tetroid(x, y) != ' ')) {
                if ((pos.x + x < 0) ||
                    (pos.x + x >= this->width) ||
                    (pos.y + y >= this->height) ||
                    (data[width * (pos.y + y) + pos.x + x] != ' ')) {
                    return true;
                }
            }
        }
    }
    return false;
}

char Playground::operator()(size_t y, size_t x) const {
    if (width * y + x < width * height)
        return data[width * y + x];
    else
        return 0;
}

bool Playground::addTetroid(const position &pos, const Tetroid &tetroid) {
    if (collision(pos, tetroid)) {
        return false;
    } else {
        for (size_t x = 0; x < 4; x++) {
            for (size_t y = 0; y < 4; y++) {
                if (tetroid(x, y) != ' ') {
                    data[width * (pos.y + y) + pos.x + x] = tetroid(x, y);
                }
            }
        }
        return true;
    }
}

void Playground::print(const position &pos) const {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if ((*this)(row, col) != ' ') {
                mvaddch(pos.y + row, pos.x + col, (*this)(row, col));
            }
        }
        //mvaddnstr(pos.y + row, pos.x, (*this)[row].c_str(), width);
    }
}
