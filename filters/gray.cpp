#include "gray.h"
#include <iostream>
GrayScaleFilter::GrayScaleFilter(){};

void GrayScaleFilter::Apply(Image& image) const {
    for (auto& row : image.pixels) {
        for (Pixel& p : row) {
            double intensity = gray_scale_consts::RedK * p.red + gray_scale_consts::GreenK * p.green +
                               gray_scale_consts::BlueK * p.blue;
            p.red = intensity;
            p.green = intensity;
            p.blue = intensity;
        }
    }
}