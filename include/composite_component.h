#pragma once

namespace pathfinder { namespace view {

	class CompositeComponent : public ComponentBase
	{
	public:
		CompositeComponent(const sf::Vector2<ComponentBase::dimension_t>& location);

		virtual ~CompositeComponent() {};

		std::shared_ptr<ComponentBase> addComponent(const std::shared_ptr<ComponentBase> component);
		std::shared_ptr<ComponentBase> getComponentAt(const sf::Vector2i& location);
		std::shared_ptr<ComponentBase> getComponentAt(const sf::Vector2<ComponentBase::dimension_t>& location);

		void onClick(sf::Event::MouseButtonEvent event) override;
		void onClickUp(sf::Event::MouseButtonEvent event) override;

		void draw() override;

	protected:
		void updateCanvas(const std::shared_ptr<ComponentBase>& component);

		std::vector<std::shared_ptr<ComponentBase>> components;
	};

}}