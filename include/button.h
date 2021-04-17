#pragma once

namespace pathfinder { namespace view {

	class Button : public ComponentBase
	{
	public:
		using dimensiont_t = ComponentBase::dimension_t;
		using Vector = ComponentBase::Vector;
		using Rect = ComponentBase::Rect;

		Button(
			sf::RenderTarget& renderTarget,
			const Rect& canvas,
			const sf::Texture& texture);

		void setPosition(const Vector& position);
		void setTexture(const sf::Texture& texture);
		void setColor(const sf::Color& color);
		void draw() override;

		void onClick(sf::Event::MouseButtonEvent event) override;
		void onClickUp(sf::Event::MouseButtonEvent event) override;

		std::function<void()> onButtonClicked = []{};
		~Button() {};

	private:
		sf::RenderTarget& renderTarget;
		sf::Vector2f m_position;
		sf::Sprite sprite;
	};

}}