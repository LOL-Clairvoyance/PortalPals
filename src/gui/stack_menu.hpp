/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:12:18
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "widget.hpp"

class StackMenu
{
public:
    StackMenu(const sf::RenderWindow& window, float baseY);
    StackMenu(const sf::Vector2f& position);

    StackMenu(StackMenu&& other);
    StackMenu& operator=(StackMenu&& other);

    ~StackMenu() = default;
    
    void AddWidget(std::unique_ptr<Widget> w);
    void SetTitle(const std::string& title);
    void HandleEvent(sf::Event e, const sf::RenderWindow& window);
    void Render(sf::RenderTarget& renderer);

private:
    const sf::RenderWindow& GetWindow() const;

    void InitWidget(Widget& w);
    
    const sf::RenderWindow* _window;
    std::vector<std::unique_ptr<Widget>> _widgets;
    sf::RectangleShape _background;
    sf::Vector2f _basePosition;
    sf::Vector2f _baseSize;

    Widget::Text _titleText;
};
