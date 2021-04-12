#include <memory>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "drawable.h"
#include "clickable.h"
#include "component_base.h"
#include "composite_component.h"

namespace pathfinder { namespace view {

	CompositeComponent::CompositeComponent(const sf::Vector2<ComponentBase::dimension_t>& location)
		: ComponentBase(location)
	{
	}

	std::shared_ptr<ComponentBase> CompositeComponent::addComponent(const std::shared_ptr<ComponentBase> component)
	{
		m_components.push_back(component);
		updateCanvas(component);
		return component;
	}

	std::shared_ptr<ComponentBase> CompositeComponent::getComponentAt(const sf::Vector2i& location)
	{
		using dim_t = ComponentBase::dimension_t;
		auto cast_location = sf::Vector2<dim_t>{ static_cast<dim_t>(location.x), static_cast<dim_t>(location.y) };
		return getComponentAt(cast_location);
	}

	std::shared_ptr<ComponentBase> CompositeComponent::getComponentAt(const sf::Vector2<ComponentBase::dimension_t>& location)
	{
		if (!contains(location))
			return nullptr;

		for (auto& component : m_components)
			if (component->contains(location))
				return component;

		return nullptr;
	}

	void CompositeComponent::updateCanvas(const std::shared_ptr<ComponentBase>& component)
	{
		auto c_canvas = component->canvas();
		auto x0 = std::min(m_canvas.left, component->canvas().left);
		auto y0 = std::min(m_canvas.top, component->canvas().top);
		auto x1 = std::max(m_canvas.left + m_canvas.width, c_canvas.left + c_canvas.width);
		auto y1 = std::max(m_canvas.top + m_canvas.height, c_canvas.top + c_canvas.height);
		m_canvas = { x0, y0, x1 - x0, y1 - y0 };
	}

	void CompositeComponent::onClick(sf::Event::MouseButtonEvent event)
	{
		auto location = sf::Vector2i{ event.x, event.y };
		auto component = getComponentAt(location);
		if (component) component->onClick(event);
	}

	void CompositeComponent::onClickUp(sf::Event::MouseButtonEvent event)
	{
		auto location = sf::Vector2i{ event.x, event.y };
		auto component = getComponentAt(location);
		if (component) component->onClickUp(event);
	}

	void CompositeComponent::draw()
	{
		for (auto& component : m_components)
			component->draw();
	}

}}