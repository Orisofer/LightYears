//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef WIDGETVALUEGAUGE_H
#define WIDGETVALUEGAUGE_H

#include "widgets/Widget.h"

namespace ly
{
    class WidgetValueGauge : public Widget
    {
    public:
        WidgetValueGauge(const sf::Vector2f& size = sf::Vector2f{300.f, 15.f},
            const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
            float initialPercentage = .75f,
            const sf::Color& backgroundCol = sf::Color(128,128,128,255),
            const sf::Color& barColorHealthy = sf::Color(128,255,128,255),
            const sf::Color& barColorInjured = sf::Color(255,255,128,255),
            const sf::Color& barColorCritical = sf::Color(255,128,128,255),
            const sf::Color& textColor = sf::Color(20,20,20,255));
        void UpdateValue(float value, float maxValue);
        sf::Vector2f GetBarSize() const;

    private:
        virtual void LocationUpdated(const sf::Vector2f &newLocation) override;
        virtual void RotationUpdated(float newRotation) override;
        virtual void Draw(sf::RenderWindow &windowRef) override;
        sf::RectangleShape m_GaugeFrontRect;
        sf::RectangleShape m_GaugeBackgroundRect;

        sf::Color m_TextColor;

        sf::Color m_BackgroundColor;
        sf::Color m_BarColorHealthy;
        sf::Color m_BarColorInjured;
        sf::Color m_BarColorCritical;

        shared<sf::Font> m_Font;
        sf::Text m_Text;
        float m_Percentage;
    };
}

#endif //WIDGETVALUEGAUGE_H
