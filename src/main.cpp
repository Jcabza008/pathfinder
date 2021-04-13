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
    c_map_width = 600,
    c_map_height = 600;

const char * const c_texturePaths[] = {
    "./images/map_point_background.png",
    "./images/map_point_background_selected_0.png",
    "./images/map_point_background_selected_1.png",
    "./images/map_point_background_selected_2.png"
};

void configureLogger()
{
    Logger::Get()
    .addStream(std::cout, LogLevel::TRACE)
    .showThreadId(true);
}

void run()
{
    // example 16x16
    constexpr std::array<int, 256> stub_map = {
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

    ComponentBase::dimension_t c_map_cols = 16;
    ComponentBase::dimension_t c_map_rows = 16;

    // core
    HeightColorProviderImpl colorProvider(-5, 5);

    // window
    AppWindow app_window;
    app_window.create();

    // components
    auto map_rect = MapView::Rect({ 0, 0, c_map_width, c_map_height});
    auto point_count = MapView::Vector({ c_map_cols, c_map_rows });
    auto texture_provider = TextureProvider(std::vector<std::string>(std::begin(c_texturePaths), std::end(c_texturePaths)));
    auto map = std::make_shared<MapView>(app_window.getWindow(), map_rect, point_count, texture_provider.getTexture("map_point_background"));

    MapView::MapPoint* point_selected = nullptr;
    ComponentBase::Vector point_selected_coords;

    for(size_t row = 0; row < c_map_rows; row++)
        for(size_t col = 0; col < c_map_cols; col++)
        {
            auto color = colorProvider.getColor(stub_map.at(row * c_map_cols + col));
            auto mapPoint = map.get()->getMapPoint(col, row)->setColor(sf::Color(color.red, color.green, color.blue));
        }

    app_window.addComponent(map);

    // hook events
    map.get()->onMapPointClicked = [&](auto point, auto coords) {
        if(point_selected)
        {
            point_selected->setTexture(texture_provider.getTexture("map_point_background"));
        }
        point_selected = point;
        point_selected_coords = coords;
        point_selected->setTexture(texture_provider.getTexture("map_point_background_selected_1"));
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