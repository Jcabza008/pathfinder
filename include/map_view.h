#pragma once

namespace pathfinder { namespace view {

	class MapView : public ComponentBase
	{
	public:
		using dimensiont_t = ComponentBase::dimension_t;
		using Vector = ComponentBase::Vector;
		using Rect = ComponentBase::Rect;

		class MapPoint
		{
		public:
			MapPoint(const Vector& position, const Vector& dimensions);
			MapPoint& setPosition(const Vector& position);
			MapPoint& setDimensions(const Vector& dimensions);
			MapPoint& setColor(const sf::Color& color);
			MapPoint& setTexture(const sf::Texture& texture);
			MapPoint& clear();
			MapPoint& draw(sf::RenderTarget& target);
		private:
			sf::Vector2f position;
			sf::Vector2f dimensions;
			sf::Color color;
			sf::Sprite m_layer;
		};

		MapView(
			sf::RenderTarget& renderTarget,
			const Rect& canvas,
			const Vector& MapPointCount,
			const sf::Texture& defaultTexture);

		void reset(const Vector& MapPointCount, const sf::Texture& defaultTexture);

		Vector getMapPointCoordsFromPoint(const Vector& point);
		Vector getMapPointCoordsFromPoint(const sf::Vector2i& point);
		MapPoint* getMapPoint(const Vector& point);
		MapPoint* getMapPoint(dimension_t row, dimension_t col);
		Vector getMapPointSize();
		Vector getLocation(dimensiont_t row, dimensiont_t col);
		void draw() override;

		void onClick(sf::Event::MouseButtonEvent event) override;
		void onClickUp(sf::Event::MouseButtonEvent event) override;

		std::function<void(MapPoint*, Vector)> onMapPointClicked = [](auto, auto) {};
		std::function<void(MapPoint*, Vector)> onMapPointRightClicked = [](auto, auto) {};

		~MapView() {};

	protected:
		sf::RenderTarget& renderTarget;
		Vector mapPointCount;
		Vector mapPointSize;
		std::vector<MapPoint> map;
		std::mutex mutex;
	};

}}