/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:08:45
 */

#include "button.hpp"

Button::Button(ButtonSize s)
{
    _button.setOutlineThickness(3);
    _button.setOutlineColor(sf::Color::Black);
    _button.setFillColor(sf::Color(0xF5F5DCFF));
    switch (s) {
        case ButtonSize::Wide:
            _button.setSize({256, 64});
            break;
        case ButtonSize::Small:
            _button.setSize({128, 64});
            break;
    }

    _text.setFillColor(sf::Color::White);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
}

void Button::SetFunction(std::function<void(void)> func)
{
    _function = func;
}

void Button::SetText(const std::string& str)
{
    _text.setString(str);
    UpdateText();
}

void Button::SetTexture(const sf::Texture& tex)
{
    _button.setTexture(&tex);
}

void Button::HandleEvent(sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            switch (e.mouseButton.button) {
                case sf::Mouse::Left:
                    if (_button.getGlobalBounds().contains((float)pos.x,
                                                            (float)pos.y)) {
                        _function();
                    }
                default:
                    break;
            }
        default:
            break;
    }
}

void Button::Render(sf::RenderTarget& renderer)
{
    renderer.draw(_button);
    renderer.draw(_text);
}

void Button::SetPosition(const sf::Vector2f& pos)
{
    _position = pos;
    _button.setPosition(_position);
    _text.setPosition(_position);
    UpdateText();
}

void Button::UpdateText()
{
    _text.setOrigin(_text.getGlobalBounds().width / 2,
                     _text.getGlobalBounds().height / 2);
    _text.move(_button.getGlobalBounds().width / 2.0f,
                _button.getGlobalBounds().height / 2.5f);
}

sf::Vector2f Button::GetSize() const
{
    return _button.getSize();
}
