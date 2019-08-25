//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_PLAYGROUND_H
#define NCURSESTETRIS_PLAYGROUND_H

#include <cstdlib>
#include <vector>

struct pos;
class Tetroid;

class Playground {

    std::vector<char> data;
    size_t width;
    size_t height;

public:
    Playground(size_t width, size_t height)
            : data(std::vector<char>(width * height)), width(width), height(height) { }

    bool collision(const pos& position, const Tetroid& tetroid);

    size_t Width() { return width; }
    size_t Height() { return height; }

    char operator()(size_t y, size_t x);
};


#endif //NCURSESTETRIS_PLAYGROUND_H
