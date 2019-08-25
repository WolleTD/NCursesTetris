//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_MATH_UTILS_H
#define NCURSESTETRIS_MATH_UTILS_H

#include "Tetroid.h"
#include <cstdlib>
#include <vector>

struct pos {
    int x;
    int y;

    pos(int x, int y) : x(x), y(y) { }

    pos& operator=(const pos& a) = default;

    pos operator+(const pos& a) const {
        return pos { a.x + x, a.y + y };
    }

    bool operator==(const pos& a) const {
        return (x == a.x && y == a.y);
    }
};

struct playground {
    std::vector<char> data;
    size_t width;
    size_t height;

    playground(size_t width, size_t height)
            : data(std::vector<char>(width * height)), width(width), height(height) { }
};

bool collision(const pos& position, const Tetroid& tetroid, const playground& pg);

#endif //NCURSESTETRIS_MATH_UTILS_H
