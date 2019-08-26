//
// Created by wolle on 25.08.19.
//

#ifndef NCURSESTETRIS_PLAYGROUND_H
#define NCURSESTETRIS_PLAYGROUND_H

#include <cstdlib>
#include <vector>

struct position;
class Tetroid;

enum class Collision {
    None,
    BorderLeft,
    BorderRight,
    PieceOrGround,
};

class Playground {

    friend class PlaygroundRow;

    std::vector<char> data;
    std::vector<size_t> markedLines;
    size_t markToggles;
    size_t width;
    size_t height;

    bool lineFilled(size_t idx) const;
    void markLine(size_t idx);
    void eraseLine(size_t idx);

public:
    Playground(size_t width, size_t height)
            : data(std::vector<char>(width * height, ' ')),
              markedLines(), markToggles(false), width(width), height(height) { }

    size_t Width() const { return width; }
    size_t Height() const { return height; }

    void print(const position& pos) const;

    Collision collision(const position& pos, const Tetroid& tetroid) const;

    size_t addTetroid(const position& pos, const Tetroid& tetroid);
    bool updateMarkedLines();

    char operator()(size_t y, size_t x) const;
};


#endif //NCURSESTETRIS_PLAYGROUND_H
