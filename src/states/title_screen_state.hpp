/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:26:17
 */

#pragma once

#include "state.hpp"
#include "gui/stack_menu.hpp"
#include "util/post_process_mask.hpp"

class TitleScreenState : public State
{
public:
    TitleScreenState(Application &game);

    virtual void HandleEvent(sf::Event) override;
    virtual void HandleInput() override;
    virtual void Update(sf::Time, sf::RenderWindow&) override {}
    virtual void FixedUpdate(sf::Time) override {}
    virtual void Render(sf::RenderTarget &renderer) override;

private:
    sf::Sprite _backgroundSprite;
    sf::Sprite _titleSprite;
    
    PostProcessMask _mask;
    StackMenu _menu;
};
