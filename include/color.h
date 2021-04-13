#pragma once

constexpr int c_positive_intercept = 0;
constexpr int c_negative_intercept = 64;

namespace pathfinder {

    struct RGBColor {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

	class HeightColorProvider
	{
	public:
		virtual RGBColor getColor(int height) = 0;
	};

    class HeightColorProviderImpl : public HeightColorProvider
    {
        public:
        HeightColorProviderImpl(int minHeight, int maxHeight);
        RGBColor getColor(int height) override;

        private:
        int maxAbsHeight;
        int positiveSlope;
        int negativeSlope;
    };

}