//
// Created by wolle on 25.08.19.
//

#include "math_utils.h"
#include <curses.h>


bool collision(const pos& position, const Tetroid& tetroid, const playground& pg) {
    // Bounds check
    if ((position.x < 0) || (position.x > pg.width - 4) || (position.y > pg.height - 4)) {
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                if ((tetroid.at(i, j) != ' ') &&
                    ((position.x + i < 0) || (position.x + i > pg.width) || (position.y + j > pg.height))) {
                    return true;
                }
            }
        }
    }
    return false;
}