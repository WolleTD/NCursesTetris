//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_TETROID_H
#define NCURSESTETRIS_TETROID_H

#include <cstddef>
#include <array>

template<int W, int H>
size_t mkindex(size_t x, size_t y, size_t rotation);

class Tetroid {
    std::array<char,17> data;
    size_t rotation;

public:
    explicit Tetroid(const char symbol[17]);

    void rotate() { rotation = (rotation + 1) % 4; }
    void unrotate() { rotation = (rotation - 1) % 4; }

    char at(size_t x, size_t y) const;

    char operator[](size_t idx) const {
        return at(idx % 4, idx / 4);
    }
};

#endif //NCURSESTETRIS_TETROID_H
