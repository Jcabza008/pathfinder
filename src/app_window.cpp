#include <memory>
#include <vector>
#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "drawable.h"
#include "clickable.h"
#include "window_base.h"
#include "component_base.h"
#include "composite_component.h"
#include "app_window.h"

constexpr char c_windowName[] = "Pathfinder";

namespace pathfinder { namespace view {

	AppWindow::AppWindow()
		: CompositeComponent({0,0})
	{
	}

	AppWindow::~AppWindow()
	{
		if (m_refresh_thread.joinable())
			m_refresh_thread.join();
	}

	AppWindow& AppWindow::create()
	{
		WindowBase::create(c_windowName);
		return *this;
	}

	void AppWindow::run()
	{
		m_refresh_thread = std::thread(&AppWindow::drawing_loop, this);
		WindowBase::run();
	}

	AppWindow& AppWindow::wait()
	{
		if (m_refresh_thread.joinable())
			m_refresh_thread.join();

		return *this;
	}

	AppWindow& AppWindow::clear()
	{
		window().clear();
		return *this;
	}

	AppWindow& AppWindow::draw_window()
	{
		draw();
		return *this;
	}

	AppWindow& AppWindow::display()
	{
		window().display();
		return *this;
	}

	bool AppWindow::isOpen()
	{
		return window().isOpen();
	}

	void AppWindow::onClose()
	{
		window().close();
	}

	void AppWindow::onClick(sf::Event::MouseButtonEvent event)
	{
		CompositeComponent::onClick(event);
	}

	void AppWindow::onClickUp(sf::Event::MouseButtonEvent event)
	{
		CompositeComponent::onClickUp(event);
	}

	AppWindow& AppWindow::refresh_wait()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		return *this;
	}

	void AppWindow::drawing_loop()
	{
		while (
			clear()
			.draw_window()
			.display()
			.refresh_wait()
			.isOpen()
		);
	}

}}