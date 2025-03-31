#include "fabric.h"

FilterPointer CreateFilter(CommandPointer cp) {
    if (FILTER_MAP.find(cp->flag) == FILTER_MAP.end()) {
        throw std::invalid_argument("No such filter " + cp->flag);
    }
    FilterType type = FILTER_MAP.at(cp->flag);
    switch (type) {
        case (FilterType::CROP):
            if (size(cp->params) != 2) {
                throw std::invalid_argument("CROP takes 2 parameters.");
            }
            return std::make_shared<CropFilter>(std::stoi(cp->params[0]), std::stoi(cp->params[1]));
            break;
        case (FilterType::NEGATIVE):
            if (size(cp->params) != 0) {
                throw std::invalid_argument("NEGATIVE takes 0 parameters.");
            }
            return std::make_shared<NegativeFilter>();
        case (FilterType::GRAYSCALE):
            if (size(cp->params) != 0) {
                throw std::invalid_argument("GRAYSCALE takes 0 parameters.");
            }
            return std::make_shared<GrayScaleFilter>();
        case (FilterType::SHARPENING):
            if (size(cp->params) != 0) {
                throw std::invalid_argument("SHARPENING takes 0 parameters.");
            }
            return std::make_shared<SharpFilter>();
        case (FilterType::EDGE_DETECTION):
            if (size(cp->params) != 1) {
                throw std::invalid_argument("EDGEDETECTION takes 1 parameters.");
            }
            return std::make_shared<EdgeDetectionFilter>(std::stod(cp->params[0]));
        case (FilterType::COLORBALANCE):
            if (size(cp->params) != 0) {
                throw std::invalid_argument("COLORBALANCE takes 0 parameters.");
            }
            return std::make_shared<ColorBalanceFilter>();
        case (FilterType::VERTICALSHRINKING):
            if (size(cp->params) != 1) {
                throw std::invalid_argument("VERTICALSHRINKING takes 1 parameters.");
            }
            return std::make_shared<VerticalShrinkFilter>(std::stoul(cp->params[0]));
        case (FilterType::HORIZONTALSHRINKING):
            if (size(cp->params) != 1) {
                throw std::invalid_argument("HORIZONTALSHRINKING takes 1 parameters.");
            }
            return std::make_shared<HorizontalShrinkFilter>(std::stoul(cp->params[0]));
        case (FilterType::SHRINKING):
            if (size(cp->params) != 2) {
                throw std::invalid_argument("SHRINKING takes 1 parameters.");
            }
            return std::make_shared<ShrinkFilter>(std::stoul(cp->params[0]), std::stoul(cp->params[1]));
        default:
            throw std::invalid_argument("CreateFilter for this filter is not implemented.");
    }
}