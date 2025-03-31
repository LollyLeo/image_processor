#include "window.h"

const std::vector<size_t> Window::WINDOW_DEFAULT_NUMBERS = {0, 1, 2, 2, 3, 4, 4, 5, 6};

Window::Window(const Image& image) : image_(image), max_index_((size(image.pixels) + 2) * (size(image.pixels[0]) + 2)) {
}
const Pixel& Window::GetByStrangeOrder(size_t n) const {
    if (n > max_index_) {
        throw std::runtime_error("Pixel in Window got out of bound");
    }
    // ignoring the fact that image is written from bottom to top
    size_t w_i = Bound(n % (image_.width + 2), static_cast<size_t>(1), image_.width);
    size_t h_i = Bound(n / (image_.width + 2), static_cast<size_t>(1), image_.height);
    return image_.pixels[h_i - 1][w_i - 1];
}

void Window::Move() {
    for (auto& x : window_) {
        x += 1;
    }
}

void Window::SetWindow(std::vector<size_t> values) {
    window_ = values;
}

void Window::SetDefault() {
    window_ = std::vector<size_t>(
        {0, 0, 0, image_.width, image_.width, image_.width, 2 * image_.width, 2 * image_.width, 2 * image_.width});
    for (size_t i = 0; i < size(window_); ++i) {
        window_[i] += Window::WINDOW_DEFAULT_NUMBERS[i];
    }
}

const Pixel& Window::GetFromWindow(size_t index) const {
    return this->GetByStrangeOrder(this->window_[index]);
}

#include <iostream>
void Window::Print() {
    for (auto x : window_) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}