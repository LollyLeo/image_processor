#include "hshrink.h"

HorizontalShrinkFilter::HorizontalShrinkFilter(size_t w) : w_(w) {
    if (w == 0) {
        throw std::invalid_argument("Shrinks must have non-zero parameters.");
    }
}

#include <iostream>

void HorizontalShrinkFilter::Apply(Image& image) const {
    std::vector<std::vector<Pixel>> new_im(image.height, std::vector<Pixel>(w_));

    for (size_t i = 0; i < image.height; ++i) {
        for (size_t j = 0; j < w_; ++j) {
            double w_cur = static_cast<double>(j) / static_cast<double>(w_) * static_cast<double>(image.width);
            size_t left = static_cast<size_t>(std::floor(w_cur));

            if (left + 1 >= image.width) {
                left = image.width - 2;
            }

            double frac = w_cur - static_cast<double>(left);
            double left_k = 1.0 - frac;
            double right_k = frac;

            Pixel p;
            p += image.pixels[i][left] * left_k;
            p += image.pixels[i][left + 1] * right_k;
            new_im[i][j] = p;
        }
    }
    image.width = w_;
    image.pixels = new_im;
}