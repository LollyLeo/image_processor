#include "negative.h"

NegativeFilter::NegativeFilter(){};
void NegativeFilter::Apply(Image& image) const {
    for (auto& row : image.pixels) {
        for (Pixel& p : row) {
            p.red = 1 - p.red;
            p.green = 1 - p.green;
            p.blue = 1 - p.blue;
        }
    }
}