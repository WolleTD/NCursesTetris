//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_NCURSES_H
#define NCURSESTETRIS_NCURSES_H

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

class NCurses {
public:
    static void drawBox(pos pos1, pos pos2, char symbol);
};


#endif //NCURSESTETRIS_NCURSES_H
