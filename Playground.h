//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_PLAYGROUND_H
#define NCURSESTETRIS_PLAYGROUND_H

#include <cstdlib>
#include <vector>

struct position;
class Tetroid;

class Playground {

    friend class PlaygroundRow;

    std::vector<char> data;
    size_t width;
    size_t height;

public:
    Playground(size_t width, size_t height)
            : data(std::vector<char>(width * height, ' ')), width(width), height(height) { }

    size_t Width() const { return width; }
    size_t Height() const { return height; }

    void print(const position& pos) const;

    bool collision(const position& pos, const Tetroid& tetroid) const;

    bool addTetroid(const position& pos, const Tetroid& tetroid);

    char operator()(size_t y, size_t x) const;
};


#endif //NCURSESTETRIS_PLAYGROUND_H
