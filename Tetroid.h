//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_TETROID_H
#define NCURSESTETRIS_TETROID_H

#include <cstddef>
#include <array>


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


class Tetroid {
    std::array<char,17> data;
    size_t rotation;

    template<int W, int H>
    size_t mkindex(size_t x, size_t y) const;

public:
    explicit Tetroid(const char symbol[17]);

    void rotate() { rotation = (rotation + 1) % 4; }
    void unrotate() { rotation = (rotation - 1) % 4; }

    char operator()(size_t x, size_t y) const;

    char operator[](size_t idx) const {
        return (*this)(idx % 4, idx / 4);
    }
};

#endif //NCURSESTETRIS_TETROID_H
