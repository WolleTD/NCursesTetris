//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_TETROID_H
#define NCURSESTETRIS_TETROID_H

#include <array>
#include <cstddef>

struct position;

class Tetroid {
    std::array<char, 17> data;
    size_t rotation;

    template <int W, int H>
    size_t mkindex(size_t x, size_t y) const;
    void print_impl(size_t y, size_t x, bool clear) const;

public:
    explicit Tetroid(const char symbol[17]);

    void rotate() { rotation = (rotation + 1) % 4; }
    void unrotate() { rotation = (rotation - 1) % 4; }

    void print(position pos) const;
    void clear(position pos) const;

    size_t Rotation() const { return rotation; }

    char operator()(size_t x, size_t y) const;

    char operator[](size_t idx) const { return (*this)(idx % 4, idx / 4); }
};

#endif  // NCURSESTETRIS_TETROID_H
