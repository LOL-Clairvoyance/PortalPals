/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:45:38
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class PostProcessMask
{
public:
    void Enable();
    void Disable();

    void Render(sf::RenderTarget& window);

    void FadeIn(float duration);
    void FadeOut(float duration);
    void FadeIn(float duration, std::function<void(void)> whenDone);
    void FadeOut(float duration, std::function<void(void)> whenDone);
private:
    sf::Clock _postProcessClock;
    sf::RectangleShape _shape;
};
