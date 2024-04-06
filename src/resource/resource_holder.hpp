/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:38:55
 */

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "resource_manager.hpp"

class ResourceHolder
{
public:
    static ResourceHolder& Get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::SoundBuffer> soundBuffers;

private:
    ResourceHolder();
};
