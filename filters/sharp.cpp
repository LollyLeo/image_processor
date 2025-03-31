#include "sharp.h"

const std::vector<double> SharpFilter::MATRIX = {0, -1, 0, -1, 5, -1, 0, -1, 0};

SharpFilter::SharpFilter(){};
void SharpFilter::Apply(Image& image) const {
    Window w = Window(image);
    std::vector<std::vector<Pixel>> new_im(image.height, std::vector<Pixel>(image.width));
    w.SetDefault();
    for (size_t i = 0; i < image.height; ++i) {
        for (size_t j = 0; j < image.width; ++j) {
            Pixel p;
            for (size_t x = 0; x < size(SharpFilter::MATRIX); ++x) {
                p += (w.GetFromWindow(x) * SharpFilter::MATRIX[x]);
            }
            p.Readjust();
            new_im[i][j] = p;
            w.Move();
        }
        w.Move();
        w.Move();
    }
    image.pixels = new_im;
}