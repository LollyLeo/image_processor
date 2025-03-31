#include "edge.h"

const std::vector<double> EdgeDetectionFilter::MATRIX = {0, -1, 0, -1, 4, -1, 0, -1, 0};

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold){};
void EdgeDetectionFilter::Apply(Image& image) const {
    GrayScaleFilter gs = {};
    gs.Apply(image);
    Window w = Window(image);
    std::vector<std::vector<Pixel>> new_im(image.height, std::vector<Pixel>(image.width));
    w.SetDefault();
    for (size_t i = 0; i < image.height; ++i) {
        for (size_t j = 0; j < image.width; ++j) {
            Pixel p;
            for (size_t x = 0; x < size(EdgeDetectionFilter::MATRIX); ++x) {
                p += (w.GetFromWindow(x) * EdgeDetectionFilter::MATRIX[x]);
            }
            p.Readjust();
            if (p.red > threshold_) {
                p = Pixel::MakeWhite();
            } else {
                p = Pixel::MakeBlack();
            }
            new_im[i][j] = p;
            w.Move();
        }
        w.Move();
        w.Move();
    }
    image.pixels = new_im;
}