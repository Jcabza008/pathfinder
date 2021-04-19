#pragma once

namespace pathfinder {

    struct RandomGeneratorConfig
    {
        // Slope variation
        double slopeVariationMean;
        double slopeVariationStd;

        // Features elevation
        double featuresElevationMean;
        double featuresElevationStd;
    };

    struct PathfinderConfig
    {
        std::string mapFilename;
        bool newMap;
        unsigned int mapWidth;
        unsigned int mapHeight;
        std::string algorithm;

        RandomGeneratorConfig randomGenConfig;
    };

    inline RandomGeneratorConfig getDefaultTerrainRandomConfig()
    {
        return RandomGeneratorConfig({
            5,    // slopeVariationMean
            1.5,  // slopeVariationStd
            50,  // featuresElevationMean
            100    // featuresElevationStd
        });
    }

    inline RandomGeneratorConfig getLowTerrainRandomConfig()
    {
        return RandomGeneratorConfig({
            5,    // slopeVariationMean
            1.5,  // slopeVariationStd
            0,    // featuresElevationMean
            100   // featuresElevationStd
        });
    }

    inline RandomGeneratorConfig getHighTerrainRandomConfig()
    {
        return RandomGeneratorConfig({
            5,    // slopeVariationMean
            1.5,  // slopeVariationStd
            150,  // featuresElevationMean
            75   // featuresElevationStd
        });
    }

}