//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_MATH_UTILS_H
#define NCURSESTETRIS_MATH_UTILS_H

class Playground;
class Tetroid;

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

bool collision(const pos& position, const Tetroid& tetroid, const Playground& pg);

#endif //NCURSESTETRIS_MATH_UTILS_H
