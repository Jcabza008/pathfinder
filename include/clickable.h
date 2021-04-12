#pragma once

namespace pathfinder { namespace view {

	class Clickable
	{
	public:
		virtual void onClick(sf::Event::MouseButtonEvent) = 0;
		virtual void onClickUp(sf::Event::MouseButtonEvent) = 0;
	};

}}