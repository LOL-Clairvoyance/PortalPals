/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:07:42
 */

#pragma once

#include <functional>

#include "widget.hpp"

enum class ButtonSize {
    Small,
    Wide,
};

class Button : public Widget
{
public:
    Button(ButtonSize s = ButtonSize::Wide);

    void SetFunction(std::function<void(void)> func);
    void SetText(const std::string& str);
    void SetTexture(const sf::Texture& tex);

    void HandleEvent(sf::Event e, const sf::RenderWindow& window) override;
    void Render(sf::RenderTarget& renderer) override;
    void SetPosition(const sf::Vector2f& pos) override;
    sf::Vector2f GetSize() const override;

    void SetColor(sf::Color color) {
        _defaultColor = color;
    }
    void SetHoverColor(sf::Color color) {
        _hoverColor = color;
    }

private:
    void UpdateText();

    sf::Vector2f _position;
    Rectangle _button;
    Text _text;
    std::function<void(void)> _function = []() {};

    sf::Color _defaultColor;
    sf::Color _hoverColor;
};

inline std::unique_ptr<Button> makeButton()
{
    return std::make_unique<Button>();
}
