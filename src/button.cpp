#include <functional>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "drawable.h"
#include "clickable.h"
#include "component_base.h"
#include "button.h"
#include "log.h"

namespace pathfinder { namespace view {

	Button::Button(sf::RenderTarget& renderTarget, const Rect& canvas, const sf::Texture& texture)
		: ComponentBase(canvas), renderTarget(renderTarget)
	{
		sprite = sf::Sprite(texture);
		setPosition({canvas.left, canvas.top});
	}

	void Button::draw()
	{
		renderTarget.draw(sprite);
	}

	void Button::setPosition(const Vector& position)
	{
		m_position = sf::Vector2f{
			static_cast<float>(position.x),
			static_cast<float>(position.y)
		};
		sprite.setPosition(m_position);
	}

	void Button::setTexture(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}

	void Button::onClick(sf::Event::MouseButtonEvent event)
	{
		pf_log_trace("mouse button " + std::to_string(event.button) + " DOWN on button");

		if (event.button == sf::Mouse::Button::Right)
			return;

		lastClicked = this;
	}

	void Button::onClickUp(sf::Event::MouseButtonEvent event)
	{
		pf_log_trace("mouse button " + std::to_string(event.button) + " UP on button");

		if (event.button == sf::Mouse::Button::Left && this == lastClicked)
		{
			pf_log_trace("matching release on button");
			onButtonClicked();
		}
		lastClicked = nullptr;
	}

}}