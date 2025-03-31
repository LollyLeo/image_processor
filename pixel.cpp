#include "pixel.h"

Pixel::Pixel(double red, double green, double blue) : red(red), green(green), blue(blue) {
}
Pixel::Pixel() : red(0), green(0), blue(0) {
}
void Pixel::operator+=(const Pixel& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
}

void Pixel::Readjust() {
    red = Bound(red, static_cast<double>(1), static_cast<double>(0));
    green = Bound(green, static_cast<double>(1), static_cast<double>(0));
    blue = Bound(blue, static_cast<double>(1), static_cast<double>(0));
}

Pixel Pixel::MakeWhite() {
    return Pixel(1, 1, 1);
}

Pixel Pixel::MakeBlack() {
    return Pixel(0, 0, 0);
}
