#pragma once
#include "image.h"
#include <stdexcept>

class Window {
public:
    explicit Window(const Image& image);
    void Move();
    void SetWindow(std::vector<size_t> values);
    void SetDefault();
    const Pixel& GetFromWindow(size_t index) const;
    void Print();

private:
    const Pixel& GetByStrangeOrder(size_t n) const;
    const Image& image_;
    const size_t max_index_;
    std::vector<size_t> window_;

    static const std::vector<size_t> WINDOW_DEFAULT_NUMBERS;
};