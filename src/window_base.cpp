#include <thread>
#include <sstream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "log.h"
#include "clickable.h"
#include "window_base.h"

namespace pathfinder { namespace view {

	WindowBase& WindowBase::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
	{
		window.create(mode, title, style, settings);
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(60);
		return deactivate();
	}

	WindowBase& WindowBase::create(const sf::String& title)
	{
		return create(sf::VideoMode(1024, 720), title);
	}

	void WindowBase::run()
	{
		pump();
	}

	WindowBase& WindowBase::activate()
	{
		setActive(true);
		return *this;
	}

	WindowBase& WindowBase::deactivate()
	{
		setActive(false);
		return *this;
	}

	void WindowBase::onClose()
	{
	}

	WindowBase::~WindowBase()
	{
		window.close();
	}

	sf::RenderWindow& WindowBase::getWindow()
	{
		return window;
	};

	void WindowBase::pump()
	{
		while (window.isOpen())
		{
			sf::Event event = {};
			if(window.waitEvent(event))
				dispatchEvent(event);
		}
	}

	void WindowBase::dispatchEvent(sf::Event event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed: onClick(event.mouseButton); break;
		case sf::Event::MouseButtonReleased: onClickUp(event.mouseButton); break;
		case sf::Event::Closed: onClose(); break;
		default: break;
		}
	}

	void WindowBase::setActive(bool active)
	{
		if (!window.setActive(active))
		{
			std::stringstream ss;
			ss << "failed to " << (active ? "activate" : "deactivate") << "window";
			auto what = ss.str();
			pf_log_error(what);
			throw std::runtime_error(what);
		}
	}

}}