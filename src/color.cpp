#include <cstdint>
#include <cmath>
#include <stdexcept>
#include "color.h"

namespace pathfinder {

    HeightColorProviderImpl::HeightColorProviderImpl(int minHeight, int maxHeight)
    {
        this->maxAbsHeight = std::max(std::abs(minHeight), std::abs(maxHeight));
        this->positiveSlope = (255 - c_positive_intercept) / this->maxAbsHeight;
        this->negativeSlope = (255 - c_negative_intercept) / this->maxAbsHeight;
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

}