//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/WidgetText.h"
#include "framework/AssetManager.h"

namespace ly
{
    WidgetText::WidgetText(const std::string &text, const std::string &fontPath,
        unsigned int fontSize) :
    m_Font(AssetManager::Get().LoadFont(fontPath))
    {
        m_Text = sf::Text(text, *(m_Font.get()), fontSize);
    }

    void WidgetText::SetText(const std::string &text)
    {
        m_Text.setString(text);
    }

    void WidgetText::SetTextSize(unsigned int size)
    {
        m_Text.setCharacterSize(size);
    }

    void WidgetText::Draw(sf::RenderWindow& windowRef)
    {
        windowRef.draw(m_Text);
    }

    void WidgetText::LocationUpdated(const sf::Vector2f &newLocation)
    {
        m_Text.setPosition(newLocation);
    }

    void WidgetText::RotationUpdated(float newRotation)
    {
        m_Text.setRotation(newRotation);
    }
}
