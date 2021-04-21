#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <thread>
#include <memory>
#include <ostream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>
#include <random>
#include <array>
#include <queue>
#include <fstream>

#include <boost/program_options.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Context.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include "log.h"

// view Libs
#include "config.h"
#include "texture_provider.h"
#include "clickable.h"
#include "drawable.h"
#include "component_base.h"
#include "composite_component.h"
#include "map_view.h"
#include "button.h"
#include "simple_views.h"
#include "window_base.h"
#include "app_window.h"

// core Libs
#include "random.h"
#include "graph.h"
#include "map.h"
#include "map_manip.h"
#include "algorithms.h"
#include "priority_queue.h"
#include "util.h"
#include "color.h"

using namespace pathfinder;
using namespace pathfinder::view;
namespace po = boost::program_options;

const char* c_fileExtension = ".pfm";

constexpr ComponentBase::dimension_t
    c_map_width = 1024,
    c_map_height = 686;

constexpr uint8_t c_pathColor_red = 0;
constexpr uint8_t c_pathColor_green = 0;
constexpr uint8_t c_pathColor_blue = 0;

const char* const c_texturePaths[] = {
    "./images/top_bar_background.png",
    "./images/map_point_background.png",
    "./images/map_point_background_selected_0.png",
    "./images/map_point_background_selected_1.png",
    "./images/map_point_background_selected_2.png",
    "./images/save.png",
    "./images/bar.png",
    "./images/search.png",
    "./images/up.png",
    "./images/down.png",
    "./images/clear.png",
    "./images/random.png",
    "./images/delete.png"
};

constexpr double c_percentOfFeaturesPerPointMean = 0.02;
constexpr double c_percentOfFeaturesPerPointStd = 0.003;
constexpr double c_percentOfMeanHeightToAffectAtOnce = 0.5;

void configureLogger(LogLevel level)
{
    Logger::Get()
    .addStream(std::cout, level)
    .showThreadId(true);
}

std::pair<int, int> findMinAndMaxValue(std::vector<int>& list)
{
    auto maxValue = INT_MIN;
    auto minValue = INT_MAX;

    for(auto it = list.cbegin(); it != list.cend(); it++)
    {
        if(*it > maxValue)
            maxValue = *it;
        if(*it < minValue)
            minValue = *it;
    }

    return {minValue, maxValue};
}

void recolorMapView(Map& map, std::shared_ptr<MapView> mapView)
{
    auto minMaxHeight = findMinAndMaxValue(map.getData());
    HeightColorProviderImpl colorProvider(minMaxHeight.first, minMaxHeight.second);

    for(size_t row = 0; row < map.getDimensions().height; row++)
        for(size_t col = 0; col < map.getDimensions().width; col++)
        {
            auto color = colorProvider.getColor(map.getData()[row * map.getDimensions().width + col]);
            mapView.get()->getMapPoint(col, row)->setColor(sf::Color(color.red, color.green, color.blue));
        }
}

void drawPath(Map& map, std::shared_ptr<MapView> mapView, std::vector<int> path)
{
    for(auto it = path.cbegin(); it != path.cend(); it++)
    {
        auto coords = map.getCoords(*it);
        mapView.get()->getMapPoint(coords.col, coords.row)->setColor(sf::Color(c_pathColor_red, c_pathColor_green, c_pathColor_blue));
    }
}

void createFile(std::fstream& file, std::string& filename)
{
    file.open(filename, std::ios::out);
    file.close();
}

void openFile(std::fstream& file, std::string& filename)
{
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
}

void truncateFile(std::fstream& file, std::string& filename)
{
    file.open(filename, std::ios::out | std::ios::trunc);
    file.close();
}

void run(PathfinderConfig config)
{
    // Load or create map
    auto filename = config.mapFilename;
    if (filename.find(c_fileExtension) == std::string::npos) {
        filename += std::string(c_fileExtension);
    }
    std::fstream mapFile;
    if(config.newMap)
    {
        createFile(mapFile, filename);
    }
    openFile(mapFile, filename);

    Map::Parser parser;
    auto map = config.newMap ? Map(Map::Dimensions({config.mapWidth, config.mapHeight})) : parser.parse(mapFile);
    pf_log_info("Loaded map. (" + std::to_string(map.getDimensions().width) + ", "+ std::to_string(map.getDimensions().height) + ")");

    // Map manipulator
    RandomNormalIntGenerator slopeVariationGenerator(config.randomGenConfig.slopeVariationMean, config.randomGenConfig.slopeVariationStd);
    MapManipulator mapManip(slopeVariationGenerator);

    // Map Random Manipulator
    RandomNormalIntGenerator featuresCountGenerator(map.size() * c_percentOfFeaturesPerPointMean, map.size() * c_percentOfFeaturesPerPointStd);
    RandomNormalIntGenerator featuresElevationGenerator(config.randomGenConfig.featuresElevationMean, config.randomGenConfig.featuresElevationStd);
    RandomUniformIntGenerator widthSelectGenerator(0, static_cast<int>(map.getDimensions().width - 1));
    RandomUniformIntGenerator heightSelectGenerator(0, static_cast<int>(map.getDimensions().height - 1));
    MapRandomManipulator mapRandomManip(mapManip, featuresCountGenerator, featuresElevationGenerator);

    // Algorithms
    DijkstrasAlgorithm dijkstras;
    AStarAlgorithm astar;

    // auxiliaty variables
    MapView::MapPoint* point_selected = nullptr;
    ComponentBase::Vector point_selected_coords;
    bool searchOn = false;

    // window
    AppWindow app_window;
    app_window.create();

    // components
    auto texture_provider = TextureProvider(std::vector<std::string>(std::begin(c_texturePaths), std::end(c_texturePaths)));
    auto map_rect = MapView::Rect({ 1, 35, c_map_width, c_map_height});
    auto point_count = MapView::Vector({ map.getDimensions().width , map.getDimensions().height });
    auto mapView = std::make_shared<MapView>(app_window.getWindow(), map_rect, point_count, texture_provider.getTexture("map_point_background"));

    auto topBarTexture = texture_provider.getTexture("top_bar_background");
    topBarTexture.setRepeated(true);
    auto topBar = std::make_shared<TopBar>(app_window.getWindow(), ComponentBase::Rect({0, 0, 1024, 34}), topBarTexture);
    auto saveButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({4, 1, 32, 32}), texture_provider.getTexture("save"));
    auto barDivisor0 = std::make_shared<BarDivisor>(app_window.getWindow(), ComponentBase::Vector({40, 2}), texture_provider.getTexture("bar"));
    auto searchButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({47, 1, 32, 32}), texture_provider.getTexture("search"));
    auto clearSearchButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({83, 1, 32, 32}), texture_provider.getTexture("delete"));
    auto barDivisor1 = std::make_shared<BarDivisor>(app_window.getWindow(), ComponentBase::Vector({119, 2}), texture_provider.getTexture("bar"));
    auto clearButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({126, 1, 32, 32}), texture_provider.getTexture("clear"));
    auto randomButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({162, 1, 32, 32}), texture_provider.getTexture("random"));
    auto upButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({198, 1, 32, 32}), texture_provider.getTexture("up"));
    auto downButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({234, 1, 32, 32}), texture_provider.getTexture("down"));


    // compose components
    topBar.get()->addComponent(saveButton);
    topBar.get()->addComponent(barDivisor0);
    topBar.get()->addComponent(searchButton);
    topBar.get()->addComponent(clearSearchButton);
    topBar.get()->addComponent(barDivisor1);
    topBar.get()->addComponent(clearButton);
    topBar.get()->addComponent(randomButton);
    topBar.get()->addComponent(upButton);
    topBar.get()->addComponent(downButton);
    app_window.addComponent(topBar);
    app_window.addComponent(mapView);

    // initial setup
    recolorMapView(map, mapView);

    if(config.visual)
    {
        mapRandomManip.on_Manipulated = [&]() {
            recolorMapView(map, mapView);
        };
    }

    // hook events
    mapView.get()->onMapPointClicked = [&](auto point, auto coords) {
        if(point_selected)
        {
            if(searchOn)
            {
                std::vector<int> path;
                if(config.algorithm == "astar")
                {

                    pf_log_info("Start finding path using A* Algorithm.");
                    path = astar.backtrack(astar.findPaths(map,
                        map.getIndex(point_selected_coords.x, point_selected_coords.y),
                        map.getIndex(coords.x, coords.y)), map.getIndex(coords.x, coords.y));
                    pf_log_info("Finished finding path using A* Algorithm.");
                }
                else
                {
                    pf_log_info("Start finding path using Dijkstra's Algorithm.");
                    path = dijkstras.backtrack(dijkstras.findPaths(map,
                        static_cast<int>(map.getIndex(point_selected_coords.x, point_selected_coords.y)),
                        static_cast<int>(map.getIndex(coords.x, coords.y))),
                        map.getIndex(point_selected_coords.x, point_selected_coords.y),
                        map.getIndex(coords.x, coords.y));
                    pf_log_info("Finished finding path using Dijkstra's Algorithm.");
                }
                drawPath(map, mapView, path);

                // deactivate search
                searchButton.get()->setColor(sf::Color(255, 255, 255));
                searchOn = !searchOn;

                return;
            }
            point_selected->setTexture(texture_provider.getTexture("map_point_background"));
        }
        point_selected = point;
        point_selected_coords = coords;
        point_selected->setTexture(texture_provider.getTexture("map_point_background_selected_1"));
    };

    saveButton.get()->onButtonClicked = [&]() {
        truncateFile(mapFile, filename);
        openFile(mapFile, filename);
        parser.deparse(map, mapFile);
    };

    searchButton.get()->onButtonClicked = [&]() {
        if(searchOn)
        {
            searchButton.get()->setColor(sf::Color(255, 255, 255));
        }
        else
        {
            searchButton.get()->setColor(sf::Color(128, 128, 128));
        }
        searchOn = !searchOn;
    };

    clearSearchButton.get()->onButtonClicked = [&]() {
        recolorMapView(map, mapView);
    };

    clearButton.get()->onButtonClicked = [&]() {
        map = Map(map.getDimensions());
        recolorMapView(map, mapView);
    };

    randomButton.get()->onButtonClicked = [&]() {
        pf_log_info("Start generating random map. (" + std::to_string(map.getDimensions().width) + ", "
            + std::to_string(map.getDimensions().height) + ") - " + "Visualization: " + std::to_string(config.visual));
        mapRandomManip.generateRandomFeatures(map, widthSelectGenerator, heightSelectGenerator);
        mapManip.blur(map);
        pf_log_info("Finished generating random map. (" + std::to_string(map.getDimensions().width) + ", "
            + std::to_string(map.getDimensions().height) + ") - " + "Visualization: " + std::to_string(config.visual));
        recolorMapView(map, mapView);
    };

    upButton.get()->onButtonClicked = [&]() {
        if(point_selected == nullptr)
            return;

        mapManip.affectHeight(map, Map::Coordinates({point_selected_coords.x, point_selected_coords.y}),
            static_cast<int>(std::abs(config.randomGenConfig.featuresElevationMean) * c_percentOfMeanHeightToAffectAtOnce));
        recolorMapView(map, mapView);
    };

    downButton.get()->onButtonClicked = [&]() {
        if(point_selected == nullptr)
            return;

        mapManip.affectHeight(map, Map::Coordinates({point_selected_coords.x, point_selected_coords.y}),
            static_cast<int>((-1) * std::abs(config.randomGenConfig.featuresElevationMean) * c_percentOfMeanHeightToAffectAtOnce));
        recolorMapView(map, mapView);
    };

    // draw until closed
    app_window.run();
    mapFile.close();
}

int main(int argc, char** argv)
{
    PathfinderConfig config = {};
    config.randomGenConfig = getDefaultTerrainRandomConfig();
    std::string preset;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("map-file", po::value<std::string>(&config.mapFilename), "map file to load (required)")
        ("new-map", "create map")
        ("debug-level", po::value<int>(&config.logLevel)->default_value(2), "log level. Supported: trace = 0, debug = 1, info = 2, warning = 3, error = 4")
        ("map-width", po::value<unsigned int>(&config.mapWidth)->default_value(800), "map width")
        ("map-height", po::value<unsigned int>(&config.mapHeight)->default_value(600), "map height")
        ("algorithm", po::value<std::string>(&config.algorithm)->default_value("dijkstras"), "algorithm to use. Supported: dijkstras and astar")
        ("preset", po::value<std::string>(&preset)->default_value(""), "random gen preset. Ignores random gen parameres. Supported: default, high and low")
        ("visual", "if pass, the map will be drawn as it is being generated")
        ("slope-var-mean", po::value<double>(&config.randomGenConfig.slopeVariationMean), "mean of random slope variation")
        ("slope-var-std", po::value<double>(&config.randomGenConfig.slopeVariationStd), "standard deviation of random slope variation")
        ("features-elevation-mean", po::value<double>(&config.randomGenConfig.featuresElevationMean), "mean of random features height")
        ("features-elevation-std", po::value<double>(&config.randomGenConfig.featuresElevationStd), "standard deviation of random features height")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        desc.print(std::cout);
        return 0;
    }

    if(!vm.count("map-file"))
    {
        std::cout << "Parameter --map-file required" << std::endl;
        return -1;
    }

    if(vm.count("new-map"))
    {
        config.newMap = true;
        if(config.mapWidth <= 0 || config.mapWidth <= 0)
        {
            std::cout << "Parameters --map-width and --map-height must be positive number" << std::endl;
            return -1;
        }
    }

    if(vm.count("preset"))
    {
        if(preset == "high")
        {
            config.randomGenConfig = getHighTerrainRandomConfig();
        }
        else if(preset == "default")
        {
            config.randomGenConfig = getDefaultTerrainRandomConfig();
        }
        else if(preset == "low")
        {
            config.randomGenConfig = getLowTerrainRandomConfig();
        }
    }

    if(vm.count("visual"))
    {
        config.visual = true;
    }

    configureLogger(LogLevel(config.logLevel));
    run(config);

    return 0;
}
