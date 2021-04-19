#include <cstdint>
#include <cmath>
#include <stdexcept>
#include "color.h"

namespace pathfinder { namespace view {

    HeightColorProviderImpl::HeightColorProviderImpl(int minHeight, int maxHeight)
    {
        this->maxAbsHeight = std::max(std::abs(minHeight), std::abs(maxHeight));
        this->positiveSlope = static_cast<double>(255 - c_positive_intercept) / static_cast<double>(this->maxAbsHeight);
        this->negativeSlope = static_cast<double>(255 - c_negative_intercept) / static_cast<double>(this->maxAbsHeight);
    }

    RGBColor HeightColorProviderImpl::getColor(int height)
    {
        if(std::abs(height) > maxAbsHeight)
            throw std::runtime_error("HeightColorProviderImpl: height out of range");

        uint8_t red = height >= 0 ? height * positiveSlope + c_positive_intercept : 0;
        uint8_t blue = height >= 0 ? 0 :  std::abs(height) * negativeSlope + c_negative_intercept;
        uint8_t green = height >= 0 ? 255 - red : 255 - blue;
        return RGBColor{red, green, blue};
    }

}}