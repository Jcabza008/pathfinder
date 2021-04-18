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

constexpr ComponentBase::dimension_t
    c_map_width = 1024,
    c_map_height = 686;

constexpr int c_oneTimeAffectHeight = 50;

const char * const c_texturePaths[] = {
    "./images/top_bar_background.png",
    "./images/map_point_background.png",
    "./images/map_point_background_selected_0.png",
    "./images/map_point_background_selected_1.png",
    "./images/map_point_background_selected_2.png",
    "./images/save.png",
    "./images/bar.png",
    "./images/search.png",
    "./images/up.png",
    "./images/down.png"
};

void configureLogger()
{
    Logger::Get()
    .addStream(std::cout, LogLevel::TRACE)
    .showThreadId(true);
}

void recolorMapView(std::shared_ptr<MapView> mapView, const std::vector<int>& map, MapView::Vector& dimensions, HeightColorProvider& colorProvider)
{
    for(size_t row = 0; row < dimensions.y; row++)
        for(size_t col = 0; col < dimensions.x; col++)
        {
            auto color = colorProvider.getColor(map[row * dimensions.x + col]);
            mapView.get()->getMapPoint(col, row)->setColor(sf::Color(color.red, color.green, color.blue));
        }
}

void run()
{
    // Map manipulator
    auto slopeVariationGenerator = std::make_shared<RandomNormalIntGenerator>(5, 1.5);
    auto mapManip = std::make_shared<MapManipulator>(slopeVariationGenerator.get());

    // Map Random Manipulator
    auto featuresCountGenerator = std::make_shared<RandomNormalIntGenerator>(10000, 1500);
    auto featuresElevationGenerator = std::make_shared<RandomNormalIntGenerator>(150, 75);
    auto mapRandomManip = std::make_shared<MapRandomManipulator>(mapManip.get(), featuresCountGenerator.get(), featuresElevationGenerator.get());

    // Map
    auto map = std::make_shared<Map>(Map::Dimensions({1024, 686}));

    // Generate Random Map
    auto widthSelectGenerator = std::make_shared<RandomUniformIntGenerator>(0, map.get()->getDimensions().width - 1);
    auto heightSelectGenerator = std::make_shared<RandomUniformIntGenerator>(0, map.get()->getDimensions().height - 1);
    mapRandomManip.get()->generateRandomFeatures(map.get(), widthSelectGenerator.get(), heightSelectGenerator.get());
    mapManip.get()->blur(map.get());

    // auxiliaty variables
    MapView::MapPoint* point_selected = nullptr;
    ComponentBase::Vector point_selected_coords;
    bool searchOn = false;

    // core
    HeightColorProviderImpl colorProvider(map.get()->getMinValue(), map.get()->getMaxValue());

    // window
    AppWindow app_window;
    app_window.create();


    // components
    auto texture_provider = TextureProvider(std::vector<std::string>(std::begin(c_texturePaths), std::end(c_texturePaths)));

    auto map_rect = MapView::Rect({ 1, 35, c_map_width, c_map_height});
    auto point_count = MapView::Vector({ map.get()->getDimensions().width , map.get()->getDimensions().height });
    auto mapView = std::make_shared<MapView>(app_window.getWindow(), map_rect, point_count, texture_provider.getTexture("map_point_background"));

    auto topBarTexture = texture_provider.getTexture("top_bar_background");
    topBarTexture.setRepeated(true);
    auto topBar = std::make_shared<TopBar>(app_window.getWindow(), ComponentBase::Rect({0, 0, 1024, 34}), topBarTexture);
    auto saveButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({4, 1, 32, 32}), texture_provider.getTexture("save"));
    auto barDivisor0 = std::make_shared<BarDivisor>(app_window.getWindow(), ComponentBase::Vector({40, 2}), texture_provider.getTexture("bar"));
    auto searchButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({47, 1, 32, 32}), texture_provider.getTexture("search"));
    auto barDivisor1 = std::make_shared<BarDivisor>(app_window.getWindow(), ComponentBase::Vector({83, 2}), texture_provider.getTexture("bar"));
    auto upButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({90, 1, 32, 32}), texture_provider.getTexture("up"));
    auto downButton = std::make_shared<Button>(app_window.getWindow(), ComponentBase::Rect({126, 1, 32, 32}), texture_provider.getTexture("down"));


    // compose components
    topBar.get()->addComponent(saveButton);
    topBar.get()->addComponent(barDivisor0);
    topBar.get()->addComponent(searchButton);
    topBar.get()->addComponent(barDivisor1);
    topBar.get()->addComponent(upButton);
    topBar.get()->addComponent(downButton);
    app_window.addComponent(topBar);
    app_window.addComponent(mapView);

    // initial setup
    recolorMapView(mapView, map.get()->getData(), point_count, colorProvider);

    // hook events
    mapView.get()->onMapPointClicked = [&](auto point, auto coords) {
        if(point_selected)
        {
            if(searchOn)
            {
                // TODO: find path
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

    upButton.get()->onButtonClicked = [&]() {
        if(point_selected == nullptr)
            return;

        mapManip.get()->affectHeight(map.get(), Map::Coordinates({point_selected_coords.x, point_selected_coords.y}), c_oneTimeAffectHeight);
        colorProvider = HeightColorProviderImpl(map.get()->getMinValue(), map.get()->getMaxValue());
        recolorMapView(mapView, map.get()->getData(), point_count, colorProvider);
    };

    downButton.get()->onButtonClicked = [&]() {
        if(point_selected == nullptr)
            return;

        mapManip.get()->affectHeight(map.get(), Map::Coordinates({point_selected_coords.x, point_selected_coords.y}), (-1) * c_oneTimeAffectHeight);
        colorProvider = HeightColorProviderImpl(map.get()->getMinValue(), map.get()->getMaxValue());
        recolorMapView(mapView, map.get()->getData(), point_count, colorProvider);
    };

    // draw until closed
    app_window.run();
}

int main(int argc, char** argv)
{
    configureLogger();

    po::options_description desc("Allowed options");
    desc.add_options()
        ("--help", "produce help message")
        ("--map-file", po::value<std::string>(), "map file to load")
        ("--new-map", po::value<bool>(), "create map")
        ("--algorithm", po::value<std::string>(), "algorithm to user. Supported: dijkstras")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("--help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
    << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }


    run();

    return 0;
}