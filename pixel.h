#pragma once

constexpr int MaxColorValue = 255;

template <typename T>
T Bound(T x, T max, T min) {
    if (max < min) {
        T swap = min;
        min = max;
        max = swap;
    }
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

class Pixel {
public:
    double red = 0;
    double green = 0;
    double blue = 0;

    Pixel(double red, double green, double blue);
    Pixel();  // to use resize in crop
    void operator+=(const Pixel& other);
    template <typename Number>
    void operator*=(const Number n) {
        red *= n;
        green *= n;
        blue *= n;
    }

    template <typename Number>
    Pixel operator*(const Number n) const {
        Pixel p = Pixel(red * n, green * n, blue * n);
        return p;
    }
    void Readjust();
    static Pixel MakeWhite();
    static Pixel MakeBlack();
};
