#include "vshrink.h"

VerticalShrinkFilter::VerticalShrinkFilter(size_t h) : h_(h) {
    if (h == 0) {
        throw std::invalid_argument("Shrinks must have non-zero parameters.");
    }
}

#include <iostream>
void VerticalShrinkFilter::Apply(Image& image) const {
    std::vector<std::vector<Pixel>> new_im(h_, std::vector<Pixel>(image.width));

    for (size_t i = 0; i < h_; ++i) {
        double h_cur = static_cast<double>(i) / static_cast<double>(h_) * static_cast<double>(image.height);
        size_t upper = static_cast<size_t>(std::floor(h_cur));

        if (upper + 1 >= image.height) {
            upper = image.height - 2;
        }

        double frac = h_cur - static_cast<double>(upper);
        double upper_k = 1.0 - frac;
        double lower_k = frac;

        for (size_t j = 0; j < image.width; ++j) {
            Pixel p;
            p += image.pixels[upper][j] * upper_k;
            p += image.pixels[upper + 1][j] * lower_k;
            new_im[i][j] = p;
        }
    }
    image.height = h_;
    image.pixels = new_im;
}