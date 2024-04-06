/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:12:33
 */

#pragma once

#include <SFML/Graphics.hpp>

class Application;

class State
{
public:
    State(Application &game)
        : _game(&game)
    {
    }

    virtual ~State() = default;

    virtual void HandleEvent(sf::Event) {}
    virtual void HandleInput() {}
    virtual void Update(sf::Time, sf::RenderWindow&) {}
    virtual void FixedUpdate(sf::Time) {}
    virtual void Render(sf::RenderTarget &renderer) {}

protected:
    Application *_game;
};
