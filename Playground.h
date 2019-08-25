//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_PLAYGROUND_H
#define NCURSESTETRIS_PLAYGROUND_H

#include <cstdlib>
#include <vector>

class Playground {

    std::vector<char> data;

public:
    size_t width;
    size_t height;
    Playground(size_t width, size_t height);
};


#endif //NCURSESTETRIS_PLAYGROUND_H
