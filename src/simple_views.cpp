#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "drawable.h"
#include "clickable.h"
#include "component_base.h"
#include "composite_component.h"
#include "simple_views.h"

#include "log.h"

namespace pathfinder { namespace view {

    TopBar::TopBar(sf::RenderTarget& _renderTarget, const ComponentBase::Rect& background_canvas, const sf::Texture& _background)
        : CompositeComponent(ComponentBase::Vector({background_canvas.left, background_canvas.top})), renderTarget(_renderTarget)
    {
        this->background.setTexture(_background);
        this->background.setTextureRect(sf::IntRect(background_canvas));
        this->background.setPosition(sf::Vector2f({static_cast<float>(background_canvas.left), static_cast<float>(background_canvas.top)}));
    }

    void TopBar::draw()
    {
        this->renderTarget.draw(this->background);
        CompositeComponent::draw();
    }

    BarDivisor::BarDivisor(sf::RenderTarget& _renderTarget, const ComponentBase::Vector& location, const sf::Texture& texture)
        : ComponentBase(location), renderTarget(_renderTarget)
    {
        this->bar.setTexture(texture);
        this->bar.setPosition(sf::Vector2f({static_cast<float>(this->canvas.left), static_cast<float>(this->canvas.top)}));
    }

    void BarDivisor::draw()
    {
        this->renderTarget.draw(this->bar);
    }

}}
