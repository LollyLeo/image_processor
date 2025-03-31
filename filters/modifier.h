#pragma once
#include <vector>
#include <memory>
#include "../fabric.h"

class Modifier {
private:
    std::vector<FilterPointer> filters_;

public:
    explicit Modifier(const std::vector<CommandPointer>& commands);
    void Apply(Image& image) const;
};