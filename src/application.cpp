/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:18:53
 */

#include "application.hpp"
#include "states/title_screen_state.hpp"

#include "resource/resource_holder.hpp"

#include <iostream>

Application::Application(unsigned int width, unsigned int height, const std::string& title)
    : _window({width, height}, title, sf::Style::Close)
{
    ResourceHolder::Get().fonts.Add("MotleyForces");

    _window.setPosition({_window.getPosition().x, _window.getPosition().y });
    _window.setFramerateLimit(60);
    PushState<TitleScreenState>(*this);
}

void Application::Run()
{
    constexpr unsigned int TPS = 60;
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned int ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while (_window.isOpen() && !_states.empty()) {
        auto& state = GetCurrentState();

        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        state.HandleInput();
        state.Update(elapsed, _window);
        _counter.Update();
        
        while (lag >= timePerUpdate) {
            ticks++;
            lag -= timePerUpdate;
            state.FixedUpdate(elapsed);
        }

        _window.clear();
        state.Render(_window);
        _counter.Draw(_window);
        _window.display();

        HandleEvent();
        TryPop();
    }
}

void Application::TryPop()
{
    if (_shouldPop) {
        _shouldPop = false;
        if (_shouldExit) {
            _states.clear();
            return;
        }
        else if (_shouldChangeState) {
            _shouldChangeState = false;
            _states.pop_back();
            PushState(std::move(_change));
            return;
        }

        _states.pop_back();
    }
}

void Application::HandleEvent()
{
    sf::Event e;

    while (_window.pollEvent(e)) {
        GetCurrentState().HandleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                _window.close();
                break;
            default:
                break;
        }
    }
}

State& Application::GetCurrentState()
{
    return *_states.back();
}

void Application::PushState(std::unique_ptr<State> state)
{
    _states.push_back(std::move(state));
}

void Application::PopState()
{
    _shouldPop = true;
}

void Application::ExitGame()
{
    _shouldPop = true;
    _shouldExit = true;
}

const sf::RenderWindow& Application::GetWindow() const
{
    return _window;
}
