//
// Created by wolle on 25.08.19.
//

#include "Playground.h"
#include "Tetroid.h"


bool Playground::collision(const pos& position, const Tetroid& tetroid) {
    // Bounds check
    if ((position.x < 0) || (position.x > this->width - 4) || (position.y > this->height - 4)) {
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                if ((tetroid(i, j) != ' ') &&
                    ((position.x + i < 0) || (position.x + i > this->width) || (position.y + j > this->height))) {
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