/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:48:02
 */

#include "post_process_mask.hpp"
#include "math.hpp"

void PostProcessMask::Enable()
{
    _shape.setFillColor(sf::Color(0, 0, 0, 255));
}

void PostProcessMask::Disable()
{
    _shape.setFillColor(sf::Color(0, 0, 0, 0));
}

void PostProcessMask::Render(sf::RenderTarget& window)
{
    window.draw(_shape);
}

void PostProcessMask::FadeIn(float duration)
{
    _postProcessClock.restart();
    _shape.setFillColor(sf::Color(0, 0, 0, (int)math::Lerp(255.0f, 0.0f, _postProcessClock.getElapsedTime().asSeconds() / duration)));
}

void PostProcessMask::FadeOut(float duration)
{
    _postProcessClock.restart();
    _shape.setFillColor(sf::Color(0, 0, 0, (int)math::Lerp(0.0f, 255.0f, _postProcessClock.getElapsedTime().asSeconds() / duration)));
}

void PostProcessMask::FadeIn(float duration, std::function<void(void)> whenDone)
{
    _postProcessClock.restart();
    _shape.setFillColor(sf::Color(0, 0, 0, math::Lerp(255.0f, 0.0f, _postProcessClock.getElapsedTime().asSeconds() / duration)));
    if (_postProcessClock.getElapsedTime().asSeconds() == duration) {
        whenDone();
    }
}

void PostProcessMask::FadeOut(float duration, std::function<void(void)> whenDone)
{
    _postProcessClock.restart();
    _shape.setFillColor(sf::Color(0, 0, 0, math::Lerp(0.0f, 255.0f, _postProcessClock.getElapsedTime().asSeconds() / duration)));
    if (_postProcessClock.getElapsedTime().asSeconds() == duration) {
        whenDone();
    }
}
