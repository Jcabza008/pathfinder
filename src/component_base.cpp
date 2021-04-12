#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "drawable.h"
#include "clickable.h"
#include "component_base.h"

namespace pathfinder { namespace view {

	void* ComponentBase::m_lastClicked;

	ComponentBase::ComponentBase(const sf::Rect<dimension_t>& canvas)
		: m_canvas(canvas)
	{
	}

	ComponentBase::ComponentBase(const sf::Vector2<dimension_t>& location)
		: ComponentBase({ location, {0, 0} })
	{
	}

	sf::Rect<ComponentBase::dimension_t> ComponentBase::canvas()
	{
		return m_canvas;
	}

	sf::Vector2<ComponentBase::dimension_t> ComponentBase::location()
	{
		return { m_canvas.left, m_canvas.top };
	}

	sf::Vector2<ComponentBase::dimension_t> ComponentBase::size()
	{
		return { m_canvas.width, m_canvas.height };
	}

	bool ComponentBase::contains(const sf::Vector2<dimension_t>& point)
	{
		return m_canvas.contains(point);
	}

}}
