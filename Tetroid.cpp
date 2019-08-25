//
// Created by wolle on 25.08.19.
//

#include "Tetroid.h"

template<int W, int H>
size_t mkindex(size_t x, size_t y, size_t rotation) {
    switch (rotation % 4) {
        case 0: return y * W + x;
        case 1: return W * (H - 1) + y - (x * W);
        case 2: return (W * H) - 1 - y * H - x;
        case 3: return W - 1 - y + (x * W);
        default: return y * W + x;
    }
}

Tetroid::Tetroid(const char symbol[17]) : data{}, rotation(0) {
    std::copy(symbol, symbol + 16, data.begin());
}

char Tetroid::at(size_t x, size_t y) const {
//        size_t shift_y = (rotation % 4 == 2) ? 1 : 0;
//        size_t shift_x = (rotation % 4 == 3) ? 1 : 0;
//        return data[mkindex<4,4>((x - shift_x) % 4, (y + shift_y) % 4, rotation)];
    return data[mkindex<4,4>(x % 4, y % 4, rotation)];
}