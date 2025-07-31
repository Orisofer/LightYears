//
// Created by Ori Sofer on 26/07/2025.
//

#include "framework/AssetManager.h"
#include "widgets/WidgetValueGauge.h"

namespace ly
{
    WidgetValueGauge::WidgetValueGauge(const sf::Vector2f &size,
        const std::string& fontPath, float initialPercentage,
        const sf::Color& backgroundCol,
        const sf::Color& barColorHealthy,
        const sf::Color& barColorInjured,
        const sf::Color& barColorCritical,
        const sf::Color& textColor)
        : m_Font(AssetManager::Get().LoadFont(fontPath)),
    m_Percentage(initialPercentage),
    m_GaugeFrontRect(size),
    m_GaugeBackgroundRect(size),
    m_BackgroundColor(backgroundCol),
    m_BarColorHealthy(barColorHealthy),
    m_BarColorInjured(barColorInjured),
    m_BarColorCritical(barColorCritical),
    m_TextColor(textColor)
    {
        std::string percentageString = std::to_string(m_Percentage);
        m_Text = sf::Text(percentageString, *(m_Font.get()), 12);
        m_Text.setFillColor(m_TextColor);

        m_GaugeBackgroundRect.setFillColor(m_BackgroundColor);
        m_GaugeFrontRect.setFillColor(m_BackgroundColor);
    }

    void WidgetValueGauge::UpdateValue(float value, float maxValue)
    {
        LOG("player health is: %f", value);
        if (maxValue == 0) return;

        std::string valueDisplayString = std::to_string((int)value) + " / " + std::to_string((int)maxValue);
        m_Text.setString(valueDisplayString);

        m_Percentage = value / maxValue;

        sf::Color barColor;

        if (m_Percentage <= .15f)
        {
            barColor = m_BarColorCritical;
        }
        else if (m_Percentage >= .15f && m_Percentage <= .75f)
        {
            barColor = m_BarColorInjured;
        }
        else
        {
            barColor = m_BarColorHealthy;
        }

        sf::Vector2f barSize = m_GaugeBackgroundRect.getSize();
        float newFrontSizeX = barSize.x * m_Percentage;
        sf::Vector2f newFrontSize = sf::Vector2f(newFrontSizeX, barSize.y);
        m_GaugeFrontRect.setSize(newFrontSize);
        m_GaugeFrontRect.setFillColor(barColor);

        CenterText();
    }

    sf::Vector2f WidgetValueGauge::GetBarSize() const
    {
        return m_GaugeBackgroundRect.getSize();
    }

    sf::FloatRect WidgetValueGauge::GetBounds() const
    {
        sf::FloatRect bounds = m_GaugeBackgroundRect.getGlobalBounds();
        return bounds;
    }

    sf::Vector2f WidgetValueGauge::GetCenter() const
    {
        return Widget::GetCenter();
    }

    void WidgetValueGauge::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(m_GaugeBackgroundRect);
        windowRef.draw(m_GaugeFrontRect);
        windowRef.draw(m_Text);
    }

    void WidgetValueGauge::CenterText()
    {
        sf::FloatRect textSize = m_Text.getGlobalBounds();

        sf::Vector2f center = GetCenter();
        m_Text.setPosition(center - sf::Vector2f(textSize.width / 2.f, textSize.height));
    }

    void WidgetValueGauge::LocationUpdated(const sf::Vector2f &newLocation)
    {
        m_GaugeBackgroundRect.setPosition(newLocation);
        m_GaugeFrontRect.setPosition(newLocation);

        CenterText();
    }

    void WidgetValueGauge::RotationUpdated(float newRotation)
    {
        m_Text.setRotation(newRotation);
        m_GaugeBackgroundRect.setRotation(newRotation);
        m_GaugeFrontRect.setRotation(newRotation);

        CenterText();
    }
}
