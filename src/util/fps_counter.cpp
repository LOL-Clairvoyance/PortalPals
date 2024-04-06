/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 15:18:12
 */

#include "fps_counter.hpp"

#include "resource/resource_holder.hpp"

#include <iostream>

FPSCounter::FPSCounter()
{
    _text.move(0, 0);
    _text.setOutlineColor(sf::Color::Black);
    _text.setFillColor({255, 255, 255});
    _text.setOutlineThickness(2);
    _text.setFont(ResourceHolder::Get().fonts.Get("MotleyForces"));
    _text.setCharacterSize(15);
}

void FPSCounter::Update()
{
    _frameCount++;

    if (_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        _fps = _frameCount / _fpsTimer.restart().asSeconds();
        _frameCount = 0;
        _delayTimer.restart();
    }
}

void FPSCounter::Draw(sf::RenderTarget& renderer)
{
    _text.setString(std::to_string((int)_fps) + " FPS");
    renderer.draw(_text);
}