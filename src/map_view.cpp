#include <vector>
#include <iostream>
#include <functional>
#include <mutex>
#include <cmath>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

#include "drawable.h"
#include "texture_provider.h"
#include "clickable.h"
#include "component_base.h"
#include "map_view.h"

#include "log.h"

namespace pathfinder { namespace view {

	MapView::MapView(
		sf::RenderTarget& renderTarget,
		const Rect& canvas,
		const Vector& mapPointCount,
		const sf::Texture& defaultTexture)
		:	ComponentBase(canvas),
			renderTarget(renderTarget)
	{
		reset(mapPointCount, defaultTexture);
	}

	void MapView::reset(const Vector& _mapPointCount, const sf::Texture& defaultTexture)
	{
		std::unique_lock<std::mutex> lock(mutex);

		mapPointCount = _mapPointCount;
		mapPointSize = getMapPointSize();
		lastClicked = nullptr;
		map.clear();

		for (dimensiont_t row = 0; row < mapPointCount.y; row++)
		for (dimensiont_t col = 0; col < mapPointCount.x; col++)
		{
			auto position = getLocation(row, col);
			auto mapPoint = MapPoint(position, mapPointSize).setTexture(defaultTexture);
			map.push_back(mapPoint);
		}
	}

	MapView::Vector MapView::getMapPointCoordsFromPoint(const Vector& point)
	{
		return { point.x / mapPointSize.x, point.y / mapPointSize.y };
	}

	MapView::Vector MapView::getMapPointCoordsFromPoint(const sf::Vector2i& point)
	{
		auto casted_point = sf::Vector2<ComponentBase::dimension_t> {
			static_cast<ComponentBase::dimension_t>(point.x),
			static_cast<ComponentBase::dimension_t>(point.y)
		};
		return getMapPointCoordsFromPoint(casted_point);
	}

	MapView::MapPoint* MapView::getMapPoint(const MapView::Vector& point)
	{
		auto coords = getMapPointCoordsFromPoint(point);
		return getMapPoint(coords.x, coords.y);
	}

	MapView::MapPoint* MapView::getMapPoint(dimension_t row, dimension_t col)
	{
		return &(map[static_cast<size_t>(row) * mapPointCount.x + col]);
	}

	void MapView::onClick(sf::Event::MouseButtonEvent event)
	{
		auto coords = getMapPointCoordsFromPoint(sf::Vector2i{ event.x, event.y });
		auto mapPoint = getMapPoint(coords.x, coords.y);
		pf_log_trace("mouse button " + std::to_string(event.button) + " DOWN on mapPoint (" + std::to_string(coords.x) + "," + std::to_string(coords.y) + ")");

		if (event.button == sf::Mouse::Button::Right)
			return onMapPointRightClicked(mapPoint, coords);

		lastClicked = mapPoint;
	}

	void MapView::onClickUp(sf::Event::MouseButtonEvent event)
	{
		auto coords = getMapPointCoordsFromPoint(sf::Vector2i{ event.x, event.y });
		auto mapPoint = getMapPoint(coords.x, coords.y);
		pf_log_trace("mouse button " + std::to_string(event.button) + " UP on mapPoint (" + std::to_string(coords.x) + "," + std::to_string(coords.y) + ")");

		if (event.button == sf::Mouse::Button::Left && mapPoint == lastClicked)
		{
			pf_log_trace("matching release on mapPoint (" + std::to_string(coords.x) + "," + std::to_string(coords.y) + ")");
			onMapPointClicked(mapPoint, coords);
		}
		lastClicked = nullptr;
	}

	MapView::Vector MapView::getMapPointSize()
	{
		auto size = std::min(canvas.width / mapPointCount.x, canvas.height / mapPointCount.y);
		return { size, size };
	}

	MapView::Vector MapView::getLocation(dimension_t col, dimension_t row)
	{
		return { col * mapPointSize.x, row * mapPointSize.y };
	}

	void MapView::draw()
	{
		std::unique_lock<std::mutex> lock(mutex);
		for (auto& mapPoint : map)
			mapPoint.draw(renderTarget);
	}

	MapView::MapPoint::MapPoint(const Vector& position, const Vector& dimensions)
		: position(sf::Vector2f{ static_cast<float>(position.x), static_cast<float>(position.y) }),
		dimensions(sf::Vector2f{ static_cast<float>(dimensions.x), static_cast<float>(dimensions.y) })
	{
		this->setPosition(position);
		m_layer.setTextureRect(sf::IntRect(0, 0, dimensions.x, dimensions.y));
	}

	MapView::MapPoint& MapView::MapPoint::setPosition(const Vector& _position)
	{
		position = sf::Vector2f{
			static_cast<float>(_position.x),
			static_cast<float>(_position.y)
		};
		m_layer.setPosition(position);

		return *this;
	}

	MapView::MapPoint& MapView::MapPoint::setDimensions(const Vector& _dimensions)
	{
		m_layer.setTextureRect(sf::IntRect(0, 0, dimensions.x, dimensions.y));
		return *this;
	}

	MapView::MapPoint& MapView::MapPoint::setTexture(const sf::Texture& texture)
	{
		m_layer.setTexture(texture);
		return *this;
	}

    MapView::MapPoint& MapView::MapPoint::setColor(const sf::Color& color)
	{
		m_layer.setColor(color);
		return *this;
	}

	MapView::MapPoint& MapView::MapPoint::clear()
	{
		m_layer = sf::Sprite();
		return *this;
	}

	MapView::MapPoint& MapView::MapPoint::draw(sf::RenderTarget& target)
	{
		target.draw(m_layer);
		return *this;
	}

}}