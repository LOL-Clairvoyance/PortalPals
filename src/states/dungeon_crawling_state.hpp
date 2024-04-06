/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-04-07 00:33:56
 */

#pragma once

#include "state.hpp"
#include "gui/stack_menu.hpp"
#include "util/post_process_mask.hpp"

#include "game/generator.hpp"
#include "game/decorator.hpp"

#include "core/rng.hpp"

#include <vector>

struct Player
{
    int x;
    int y;
};

class Level
{
public:
    Level(int floorCount, const sf::Font& font);
    ~Level();

    void HandleEvent(sf::Event);
    void Render(sf::RenderTarget &renderer);

private:
    std::vector<Map> _floors;
    int _floorIndex;
    Map *_currentFloor;

    Player _player;
    sf::Text _floorText;
};

class DungeonCrawlingState : public State
{
public:
    DungeonCrawlingState(Application &game);

    virtual void HandleEvent(sf::Event) override;
    virtual void HandleInput() override;
    virtual void Update(sf::Time, sf::RenderWindow&) override {}
    virtual void FixedUpdate(sf::Time) override {}
    virtual void Render(sf::RenderTarget &renderer) override;

private:
    Level _level;
    
    PostProcessMask _mask;
    StackMenu _menu;
};
