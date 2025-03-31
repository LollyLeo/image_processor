#include "balance.h"
ColorBalanceFilter::ColorBalanceFilter(){};
void ColorBalanceFilter::Apply(Image& image) const {
    Pixel intensity = Pixel();
    for (auto& row : image.pixels) {
        for (Pixel& p : row) {
            intensity += p;
        }
    }
    intensity.red = 1 / intensity.red;
    intensity.green = 1 / intensity.green;
    intensity.blue = 1 / intensity.blue;
    intensity *= 3 / (intensity.red + intensity.green + intensity.blue);
    for (auto& row : image.pixels) {
        for (Pixel& p : row) {
            p.red *= intensity.red;
            p.green *= intensity.green;
            p.blue *= intensity.blue;
            p.Readjust();
        }
    }
}