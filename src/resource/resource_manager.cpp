/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:43:50
 */

#include "resource_holder.hpp"

ResourceHolder& ResourceHolder::Get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
    : fonts("fonts", "ttf"), textures("textures", "png"), soundBuffers("sfx", "ogg")
{
}
