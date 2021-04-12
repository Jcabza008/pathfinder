#pragma once

namespace pathfinder { namespace view {

	class ComponentBase : public Clickable, public Drawable
	{
	public:
		using dimension_t = unsigned int;
		using Vector = sf::Vector2<ComponentBase::dimension_t>;
		using Rect = sf::Rect<ComponentBase::dimension_t>;

		virtual ~ComponentBase() {};

		sf::Rect<dimension_t> canvas();
		sf::Vector2<dimension_t> location();
		sf::Vector2<dimension_t> size();
		bool contains(const sf::Vector2<dimension_t>& point);

	protected:
		ComponentBase(const sf::Rect<dimension_t>& canvas);
		ComponentBase(const sf::Vector2<dimension_t>& location);

		sf::Rect<dimension_t> m_canvas;

		static void* m_lastClicked;
	};

}}