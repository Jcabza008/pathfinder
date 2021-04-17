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
#include "graph.h"
#include "algorithms.h"
#include "priority_queue.h"
#include "util.h"
#include "color.h"

using namespace pathfinder;
using namespace pathfinder::view;

constexpr ComponentBase::dimension_t
    c_map_width = 1024,
    c_map_height = 686;

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

void recolorMapView(std::shared_ptr<MapView> mapView, int* map, MapView::Vector& dimensions, HeightColorProvider& colorProvider)
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
    // example 16x16
    ComponentBase::dimension_t c_map_cols = 16;
    ComponentBase::dimension_t c_map_rows = 16;
    int stub_map[256] = {
         1,  1,  1,  0, -1, -2, -3, -5, -2, -1,  0,  0,  0,  0,  1,  2,
         1,  1,  2,  1,  1,  1, -2, -3, -3, -2, -1,  0,  1,  1,  2,  2,
         1,  2,  2,  2,  1,  1, -1, -2, -2, -2, -1,  0,  1,  2,  3,  4,
         1,  2,  3,  2,  1,  0,  0, -1, -1, -1,  0,  0,  1,  2,  4,  5,
         1,  3,  4,  2,  2,  1,  1,  0,  0, -1,  0,  1,  1,  3,  5,  5,
         2,  3,  4,  3,  2,  2,  1,  0,  0,  0,  0,  2,  2,  4,  5,  4,
         2,  4,  5,  5,  3,  2,  1,  1,  0,  0,  1,  2,  3,  5,  5,  3,
         2,  2,  4,  5,  5,  3,  2,  1,  0,  0,  2,  3,  5,  5,  4,  3,
         1,  2,  3,  4,  5,  4,  3,  1,  1,  1,  1,  2,  5,  4,  3,  2,
         1,  1,  2,  4,  4,  3,  2,  2,  2,  2,  3,  3,  4,  4,  2,  2,
         0,  1,  2,  3,  3,  2,  2,  3,  4,  3,  2,  2,  3,  3,  2,  1,
         0,  1,  1,  2,  2,  1,  1,  2,  3,  2,  1,  2,  2,  2,  1,  1,
         0,  0,  1,  2,  1,  1,  1,  1,  2,  1,  1,  2,  2,  1,  1,  0,
        -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  2,  1,  1,  0,  0,
        -1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
        -2, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    // auxiliaty variables
    MapView::MapPoint* point_selected = nullptr;
    ComponentBase::Vector point_selected_coords;
    bool searchOn = false;

    // core
    HeightColorProviderImpl colorProvider(-5, 5);

    // window
    AppWindow app_window;
    app_window.create();


    // components
    auto texture_provider = TextureProvider(std::vector<std::string>(std::begin(c_texturePaths), std::end(c_texturePaths)));

    auto map_rect = MapView::Rect({ 1, 35, c_map_width, c_map_height});
    auto point_count = MapView::Vector({ c_map_cols, c_map_rows });
    auto map = std::make_shared<MapView>(app_window.getWindow(), map_rect, point_count, texture_provider.getTexture("map_point_background"));

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
    app_window.addComponent(map);

    // initial setup
    recolorMapView(map, stub_map, point_count, colorProvider);

    // hook events
    map.get()->onMapPointClicked = [&](auto point, auto coords) {
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

        // TODO: perform action on map

        // TODO: redraw map
        // eg
        recolorMapView(map, stub_map, point_count, colorProvider);
    };

    downButton.get()->onButtonClicked = [&]() {
        if(point_selected == nullptr)
            return;

        // TODO: perform action on map

        // TODO: redraw map
        // eg
        recolorMapView(map, stub_map, point_count, colorProvider);
    };

    // draw until closed
    app_window.run();
}

int main()
{
    configureLogger();
    run();

    return 0;
}