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
    }

    sf::FloatRect WidgetButton::GetBounds() const
    {
        return m_Sprite.getGlobalBounds();
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
        sf::FloatRect textBounds = m_Text.getGlobalBounds();
        sf::FloatRect backgroundBounds = m_Sprite.getGlobalBounds();
        sf::Vector2f textHalf = sf::Vector2f(textBounds.width / 2.f, textBounds.height / 2.f);
        sf::Vector2f backgroundPosition = m_Sprite.getPosition();

        sf::Vector2f backgroundCenterPos = sf::Vector2f(backgroundPosition.x + backgroundBounds.width / 2.f,
            backgroundPosition.y + backgroundBounds.height / 2.f);

        sf::Vector2f textFinalPos = sf::Vector2f(backgroundCenterPos.x - textHalf.x, backgroundCenterPos.y - textBounds.height);

        m_Text.setPosition(textFinalPos);
    }
}
