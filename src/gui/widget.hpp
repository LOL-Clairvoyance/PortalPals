/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:03:46
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "resource/resource_holder.hpp"

class Widget
{
public:
    virtual void HandleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
    virtual void Render(sf::RenderTarget& renderTarget) = 0;
    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual sf::Vector2f GetSize() const = 0;

    class Text : public sf::Text {
        public:
            Text();
    };

    class Rectangle : public sf::RectangleShape {
        public:
            bool IsRolledOn(const sf::RenderWindow& window) const;
            bool IsClicked(sf::Event event, const sf::RenderWindow& window);
    };
};
