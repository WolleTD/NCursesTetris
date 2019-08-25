//
// Created by wolle on 25.08.19.
//

#include "NCurses.h"
#include "Playground.h"
#include "Tetroid.h"


bool Playground::collision(const pos& position, const Tetroid& tetroid) {
    for (size_t x = 0; x < 4; x++) {
        for (size_t y = 0; y < 4; y++) {
            if ((tetroid(x, y) != ' ')) {
                if ((position.x + x < 0) ||
                    (position.x + x > this->width) ||
                    (position.y + y > this->height) ||
                    (data[width * y + x] != ' ')) {
                    return true;
                }
            }
        }
    }
    return false;
}

char Playground::operator()(size_t y, size_t x) {
    if (width * y + x < width * height)
        return data[width * y + x];
    else
        return 0;
}