#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Context.hpp>
#include <SFML/Window/Event.hpp>

#include "log.h"

// view Libs
#include "clickable.h"
#include "drawable.h"
#include "component_base.h"
#include "composite_component.h"
#include "button.h"
#include "window_base.h"
#include "app_window.h"

// core Libs
#include "graph.h"
#include "algorithms.h"
#include "priority_queue.h"
#include "util.h"

using namespace pathfinder;
using namespace pathfinder::view;

void configureLogger()
{
    Logger::Get()
    .addStream(std::cout, LogLevel::TRACE)
    .showThreadId(true);
}

void run()
{
    // core

    // window
    AppWindow app_window;
    app_window.create();

    // components

    // hook events

    // draw until closed
    app_window.run();
}

int main()
{
    configureLogger();
    run();

    return 0;
}