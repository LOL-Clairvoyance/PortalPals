/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:09:55
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

#include "states/state.hpp"
#include "util/fps_counter.hpp"

class Application
{
public:
    Application(unsigned int width, unsigned int height, const std::string& title);

    void Run();

    template<typename T, typename... Args>
    void PushState(Args&&... args);
    void PushState(std::unique_ptr<State> state);
    void PopState();
    void ExitGame();

    template<typename T, typename... Args>
    void ChangeState(Args&&... args);
    
    const sf::RenderWindow& GetWindow() const;

private:
    void HandleEvent();
    void TryPop();

    State& GetCurrentState();

    sf::RenderWindow _window;
    std::vector<std::unique_ptr<State>> _states;

    FPSCounter _counter;

    bool _shouldPop = false;
    bool _shouldExit = false;
    bool _shouldChangeState = false;
    std::unique_ptr<State> _change;
};

template <typename T, typename... Args>
inline void Application::PushState(Args&&... args)
{
    PushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
inline void Application::ChangeState(Args&&... args)
{
    _change = std::make_unique<T>(std::forward<Args>(args)...);
    _shouldPop = true;
    _shouldChangeState = true;
}
