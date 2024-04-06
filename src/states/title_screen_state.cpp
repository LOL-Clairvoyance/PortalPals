/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:27:45
 */

#include "title_screen_state.hpp"
#include "application.hpp"
#include "dungeon_crawling_state.hpp"

#include "resource/resource_holder.hpp"

#include "gui/button.hpp"

TitleScreenState::TitleScreenState(Application &game)
    : State(game), _menu(game.GetWindow(), 500)
{
    ResourceHolder::Get().textures.Add("title_background");
    ResourceHolder::Get().textures.Add("title");

    auto backgroundTexture = ResourceHolder::Get().textures.Get("title_background");
    auto titleTexture = ResourceHolder::Get().textures.Get("title");

    _backgroundSprite.setTexture(ResourceHolder::Get().textures.Get("title_background"));
    _backgroundSprite.setPosition({0, 0});
    _backgroundSprite.setScale(2.0f, 2.0f);
    _backgroundSprite.setColor(sf::Color(255, 255, 255, 100));

    _titleSprite.setTexture(ResourceHolder::Get().textures.Get("title"));
    _titleSprite.setPosition({(1920.0f / 2.0f) - (titleTexture.getSize().x / 2.0f), 100.0f});

    auto bp = std::make_unique<Button>();
    bp->SetText("PLAY");
    bp->SetFunction([&] {
        game.PushState<DungeonCrawlingState>(game);
    });

    auto bq = std::make_unique<Button>();
    bq->SetText("QUIT");
    bq->SetFunction([&] {
        _game->ExitGame();
    });

    _menu.AddWidget(std::move(bp));
    _menu.AddWidget(std::move(bq));

    _mask.Enable();
}

void TitleScreenState::HandleEvent(sf::Event event)
{
    _menu.HandleEvent(event, _game->GetWindow());
}

void TitleScreenState::HandleInput()
{
}

void TitleScreenState::Render(sf::RenderTarget &renderer)
{
    renderer.draw(_backgroundSprite);
    renderer.draw(_titleSprite);

    _menu.Render(renderer);

    _mask.Render(renderer);
}
