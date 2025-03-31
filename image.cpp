#include "image.h"

Image::Image(std::vector<std::vector<Pixel>> pixels) : pixels(pixels), height(size(pixels)), width(size(pixels[0])) {
}