/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:06:42
 */

#include "widget.hpp"

Widget::Text::Text()
{
    setCharacterSize(25);
    setOutlineColor(sf::Color::Black);
    setFillColor(sf::Color::White);
    setFont(ResourceHolder::Get().fonts.Get("MotleyForces"));
}

bool Widget::Rectangle::IsRolledOn(const sf::RenderWindow& window) const
{
    auto pos = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains((float)pos.x, (float)pos.y);
}

bool Widget::Rectangle::IsClicked(sf::Event e, const sf::RenderWindow& window)
{
    if (IsRolledOn(window)) {
        if (e.type == sf::Event::MouseButtonPressed) {
            return e.mouseButton.button == sf::Mouse::Left;
        }
    }
    return false;
}
