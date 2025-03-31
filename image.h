#pragma once
#include <vector>
#include <queue>
#include "pixel.h"

class Image {
public:
    explicit Image(std::vector<std::vector<Pixel>> pixels);

    std::vector<std::vector<Pixel>> pixels;
    size_t height;
    size_t width;
};
