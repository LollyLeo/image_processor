#include "shrink.h"

ShrinkFilter::ShrinkFilter(size_t h, size_t w) : h_(h), w_(w) {
}

#include <iostream>
void ShrinkFilter::Apply(Image& image) const {
    std::vector<std::vector<Pixel>> new_im(h_, std::vector<Pixel>(w_));

    for (size_t i = 0; i < h_; ++i) {
        double h_cur = static_cast<double>(i) / static_cast<double>(h_) * static_cast<double>(image.height);
        size_t upper = static_cast<size_t>(std::floor(h_cur));
        if (upper + 1 >= image.height) {
            upper = image.height - 2;
        }
        double frac_h = h_cur - static_cast<double>(upper);
        double upper_k = 1.0 - frac_h;
        double lower_k = frac_h;

        for (size_t j = 0; j < w_; ++j) {
            double w_cur = static_cast<double>(j) / static_cast<double>(w_) * static_cast<double>(image.width);
            size_t left = static_cast<size_t>(std::floor(w_cur));
            if (left + 1 >= image.width) {
                left = image.width - 2;
            }
            double frac_w = w_cur - static_cast<double>(left);
            double left_k = 1.0 - frac_w;
            double right_k = frac_w;

            Pixel p;
            p += image.pixels[upper][left] * (upper_k * left_k);
            p += image.pixels[upper][left + 1] * (upper_k * right_k);
            p += image.pixels[upper + 1][left] * (lower_k * left_k);
            p += image.pixels[upper + 1][left + 1] * (lower_k * right_k);
            new_im[i][j] = p;
        }
    }
    image.height = h_;
    image.width = w_;
    image.pixels = new_im;
}