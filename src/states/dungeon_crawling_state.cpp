/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:27:45
 */

#include "dungeon_crawling_state.hpp"
#include "application.hpp"

#include "resource/resource_holder.hpp"

#include "gui/button.hpp"

Level::Level(int floorCount, const sf::Font& font)
{
    auto generator = DungeonGenerator::CreateGenerator(GeneratorType::Tunneling);

    _floors.resize(floorCount);
    for (auto& floor : _floors) {
        floor.width = 100;
        floor.height = 60;
    
        generator->GenerateMap(floor);
        DungeonDecorator::DecorateDungeon(floor);
    }

    _floorIndex = 0;
    _currentFloor = &_floors[_floorIndex];

    _player.x = _floors[0].startX;
    _player.y = _floors[0].startY;

    _floorText.setFont(font);
    _floorText.setCharacterSize(50);
    _floorText.setPosition(10, 950);
}

Level::~Level()
{

}

void Level::HandleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left: {
                if (_currentFloor->map[_player.x - 1][_player.y] != Tile::Solid) {
                    _player.x -= 1;
                }
                break;
            }
            case sf::Keyboard::Right: {
                if (_currentFloor->map[_player.x + 1][_player.y] != Tile::Solid) {
                    _player.x += 1;
                }
                break;
            }
            case sf::Keyboard::Down: {
                if (_currentFloor->map[_player.x][_player.y + 1] != Tile::Solid) {
                    _player.y += 1;
                }
                break;
            }
            case sf::Keyboard::Up: {
                if (_currentFloor->map[_player.x][_player.y - 1] != Tile::Solid) {
                    _player.y -= 1;
                }
                break;
            }
        }
    }
}

void Level::Render(sf::RenderTarget &renderer)
{
    bool newFloor = false;

    _currentFloor->UpdateDiscovery(_player.x, _player.y);

    for (int i = 0; i < _currentFloor->width; i++) {
        for (int j = 0; j < _currentFloor->height; j++) {
            sf::RectangleShape shape;
            shape.setSize(sf::Vector2f(1920 / _currentFloor->width, 1080 / _currentFloor->height));
            shape.setPosition(sf::Vector2f(i * (1920 / _currentFloor->width), j * (1080 / _currentFloor->height)));
            if (_currentFloor->map[i][j] == Tile::Walkable) {
                shape.setFillColor(sf::Color::Green);
            } else if (_currentFloor->map[i][j] == Tile::Stairs) {
                shape.setFillColor(sf::Color::Red);
                if (_player.x == i && _player.y == j) {
                    newFloor = true;
                }
            } else {
                shape.setFillColor(sf::Color::Black);
            }
            if (_player.x == i && _player.y == j) {
                shape.setFillColor(sf::Color::Blue);
            }
            if (_currentFloor->discovered[i][j] == 1) {
                renderer.draw(shape);
            }
        }
    }

    if (newFloor) {
        if (_floorIndex < _floors.size() - 1) {
            _floorIndex++;
        }
        _currentFloor = &_floors[_floorIndex];
        _player.x = _currentFloor->startX;
        _player.y = _currentFloor->startY;
    }

    _floorText.setString(std::to_string(_floorIndex) + "F");
    renderer.draw(_floorText);
}

DungeonCrawlingState::DungeonCrawlingState(Application &game)
    : State(game), _menu(game.GetWindow(), 300), _level(RNG::pRNG.GetIntInRange(2, 6), ResourceHolder::Get().fonts.Get("MotleyForces"))
{
    
}

void DungeonCrawlingState::HandleEvent(sf::Event event)
{
    _menu.HandleEvent(event, _game->GetWindow());
    _level.HandleEvent(event);
}

void DungeonCrawlingState::HandleInput()
{
    
}

void DungeonCrawlingState::Render(sf::RenderTarget &renderer)
{
    _level.Render(renderer);
}
