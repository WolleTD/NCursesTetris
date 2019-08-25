//
// Created by wolle on 25.08.19.
//

#include "Playground.h"

Playground::Playground(size_t width, size_t height)
        : data(std::vector<char>(width * height)), width(width), height(height) { }