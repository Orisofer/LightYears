//
// Created by Ori Sofer on 01/08/2025.
//

#include "widgets/WidgetButton.h"
#include "framework/AssetManager.h"

namespace ly
{
    WidgetButton::WidgetButton(const std::string& text, const std::string& texturePath, const std::string& fontPath,
        sf::Color colorDefault, sf::Color colorClicked, sf::Color colorHover, sf::Color colorText) :
    m_Texture(AssetManager::Get().LoadTexture(texturePath)),
    m_Font(AssetManager::Get().LoadFont(fontPath)),
    m_ColorDefault(colorDefault),
    m_ColorClicked(colorClicked),
    m_ColorHover(colorHover),
    m_ColorText(colorText),
    m_IsDown(false)
    {
        InitText(text);
        InitSprite();
        SetColor(m_ColorDefault);
        CenterText();
    }

    sf::FloatRect WidgetButton::GetBounds() const
    {
        return m_Sprite.getGlobalBounds();
    }

    bool WidgetButton::HandleEvent(const sf::Event &event)
    {
        bool handled = false;

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (m_Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && m_IsDown)
                {
                    OnClick.Broadcast();
                    handled = true;
                }
            }

            ButtonUp();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (m_Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !m_IsDown)
            {
                ButtonDown();
                handled = true;
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (m_Sprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                {
                    MouseHover();
                }
                else
                {
                    ButtonUp();
                }

                handled = true;
            }
        }

        return handled || Widget::HandleEvent(event);
    }

    void WidgetButton::ButtonUp()
    {
        SetColor(m_ColorDefault);
        m_IsDown = false;
    }

    void WidgetButton::ButtonDown()
    {
        SetColor(m_ColorClicked);
        m_IsDown = true;
    }

    void WidgetButton::MouseHover()
    {
        SetColor(m_ColorHover);
    }

    void WidgetButton::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(m_Sprite);
        windowRef.draw(m_Text);
    }

    void WidgetButton::LocationUpdated(const sf::Vector2f &newLocation)
    {
        m_Sprite.setPosition(newLocation);

        CenterText();
    }

    void WidgetButton::RotationUpdated(float newRotation)
    {
        m_Sprite.setRotation(newRotation);
        m_Text.setRotation(newRotation);

        CenterText();
    }

    void WidgetButton::SetColor(const sf::Color &color)
    {
        m_Sprite.setColor(color);
    }

    void WidgetButton::InitSprite()
    {
        m_Sprite = sf::Sprite(*m_Texture);
    }

    void WidgetButton::InitText(const std::string& text)
    {
        m_Text = sf::Text(text, *m_Font, 14);
        m_Text.setFillColor(m_ColorText);
    }

    void WidgetButton::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenter();
        sf::FloatRect textBounds = m_Text.getGlobalBounds();
        sf::Vector2f centeredText = sf::Vector2f(widgetCenter.x - (textBounds.width / 2),widgetCenter.y - (textBounds.height));

        m_Text.setPosition(centeredText);
    }
}
