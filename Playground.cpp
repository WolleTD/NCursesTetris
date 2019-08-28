//
// Created by wolle on 25.08.19.
//

#include "Playground.h"
#include <curses.h>
#include <algorithm>
#include "NCurses.h"
#include "Tetroid.h"

Collision Playground::collision(const position &pos, const Tetroid &tetroid) const {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if ((tetroid(x, y) != ' ')) {
                if (pos.x + x < 0) {
                    return Collision::BorderLeft;
                } else if (pos.x + x >= this->width) {
                    return Collision::BorderRight;
                } else if ((pos.y + y >= this->height) || (data[width * (pos.y + y) + pos.x + x] != ' ')) {
                    return Collision::PieceOrGround;
                }
            }
        }
    }
    return Collision::None;
}

char Playground::operator()(size_t y, size_t x) const {
    if (width * y + x < width * height)
        return data[width * y + x];
    else
        return 0;
}

size_t Playground::addTetroid(const position &pos, const Tetroid &tetroid) {
    for (size_t x = 0; x < 4; x++) {
        for (size_t y = 0; y < 4; y++) {
            if (tetroid(x, y) != ' ') {
                data[width * (pos.y + y) + pos.x + x] = tetroid(x, y);
            }
        }
    }
    size_t rows = 0;
    for (size_t row = pos.y; row < std::min((size_t)pos.y + 4, height); row++) {
        if (lineFilled(row)) {
            rows++;
            markLine(row);
            markedLines.push_back(row);
        }
    }
    return rows;
}

void Playground::print(const position &pos) const {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            mvaddch(pos.y + row, pos.x + col, (*this)(row, col));
        }
    }
}

bool Playground::lineFilled(size_t idx) const {
    auto lineBegin = data.begin() + idx * width;
    auto lineEnd = lineBegin + width;
    return std::find(lineBegin, lineEnd, ' ') == lineEnd;
}

void Playground::markLine(size_t idx) {
    auto lineBegin = data.begin() + idx * width;
    auto lineEnd = lineBegin + width;
    bool markBlank = (markToggles % 2 == 1);
    std::fill(lineBegin, lineEnd, (markBlank ? ' ' : '='));
}

void Playground::eraseLine(size_t idx) {
    auto lineBegin = data.begin() + idx * width;
    auto lineEnd = lineBegin + width;
    std::copy_backward(data.begin(), lineBegin, lineEnd);
    std::fill(data.begin(), data.begin() + width, ' ');
}

bool Playground::updateMarkedLines() {
    if (markedLines.empty()) return false;
    // Flash two times, erase on toggles == 5
    if (++markToggles == 6) {
        for (auto line : markedLines) {
            eraseLine(line);
        }
        markToggles = 0;
        markedLines.clear();
    } else {
        for (auto line : markedLines) {
            markLine(line);
        }
    }
    return true;
}
