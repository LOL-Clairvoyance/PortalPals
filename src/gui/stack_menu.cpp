/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:13:39
 */

#include "stack_menu.hpp"

StackMenu::StackMenu(const sf::RenderWindow& window, float baseY)
    : _basePosition((float)window.getSize().x / 2.0f, baseY)
    , _baseSize(300, 20)
{
    _background.setOutlineThickness(2);
    _background.setOutlineColor(sf::Color::Green);
    _background.setFillColor({100, 100, 100, 230});
    _background.setSize(_baseSize);
    _background.setPosition(_basePosition.x - _baseSize.x / 2, baseY - 30);
    _titleText.setPosition(0, baseY - 35);
    _titleText.setOutlineColor(sf::Color::Black);
    _titleText.setOutlineThickness(1);
    _titleText.setCharacterSize(30);
}

StackMenu::StackMenu(const sf::Vector2f& position)
    : _basePosition(position)
    , _baseSize(300, 20)
{
    _background.setFillColor({100, 100, 100, 128});
    _background.setSize(_baseSize);
    _background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
    : _widgets(std::move(other._widgets))
    , _background(std::move(other._background))
    , _basePosition(other._basePosition)
    , _baseSize(other._baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    _widgets = std::move(other._widgets);
    _background = std::move(other._background);
    _basePosition = other._basePosition;
    _baseSize = other._baseSize;
    return *this;
}

void StackMenu::AddWidget(std::unique_ptr<Widget> w)
{
    InitWidget(*w);
    _widgets.push_back(std::move(w));
}

void StackMenu::InitWidget(Widget& widget)
{
    widget.SetPosition({_basePosition.x - widget.GetSize().x / 2, _basePosition.y});
    _basePosition.y += widget.GetSize().y + 25;
    _baseSize.y += widget.GetSize().y + 25;
    _background.setSize(_baseSize);
}

void StackMenu::SetTitle(const std::string& title)
{
    _titleText.setString(title);
    _titleText.setPosition(GetWindow().getSize().x -
                            _titleText.getGlobalBounds().width / 2,
                            _titleText.getPosition().y);
}

void StackMenu::HandleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : _widgets) {
        widget->HandleEvent(e, window);
    }
}

void StackMenu::Render(sf::RenderTarget& renderer)
{
    //renderer.draw(_background);
    renderer.draw(_titleText);
    for (auto& widget : _widgets) {
        widget->Render(renderer);
    }
}

const sf::RenderWindow& StackMenu::GetWindow() const
{
    return *_window;
}
