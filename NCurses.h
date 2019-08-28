//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_NCURSES_H
#define NCURSESTETRIS_NCURSES_H

struct position {
    int x;
    int y;

    position(int x, int y) : x(x), y(y) {}

    position& operator=(const position& a) = default;

    position operator+(const position& a) const { return position{x + a.x, y + a.y}; }

    position operator-(const position& a) const { return position{x - a.x, y - a.y}; }

    bool operator==(const position& a) const { return (x == a.x && y == a.y); }

    bool operator!=(const position& a) const { return !((*this) == a); }
};

class NCurses {
public:
    static void drawBox(position pos1, position pos2, char symbol);
};

#endif  // NCURSESTETRIS_NCURSES_H
