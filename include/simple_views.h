#pragma once

namespace pathfinder { namespace view {

    class TopBar : public CompositeComponent
    {
        public:
        TopBar(sf::RenderTarget& renderTarget, const ComponentBase::Rect& canvas, const sf::Texture& background);
        void draw() override;

        private:
        sf::RenderTarget& renderTarget;
        sf::Sprite background;
    };

    class BarDivisor : public ComponentBase
    {
        public:
        BarDivisor(sf::RenderTarget& renderTarget, const ComponentBase::Vector& location, const sf::Texture& texture);
        void draw() override;
        void onClick(sf::Event::MouseButtonEvent) override {};
        void onClickUp(sf::Event::MouseButtonEvent) override {};

        private:
        sf::RenderTarget& renderTarget;
        sf::Sprite bar;
    };

}}