#pragma once
#include <memory>
#include "../image.h"

class Filter {
public:
    virtual void Apply(Image& image) const = 0;
    virtual ~Filter() = default;
};

using FilterPointer = std::shared_ptr<Filter>;