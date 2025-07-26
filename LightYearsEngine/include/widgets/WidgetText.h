//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef WIDGETTEXT_H
#define WIDGETTEXT_H

#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
    class WidgetText : public Widget
    {
    public:
        WidgetText(const std::string& text,
            const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
            unsigned int fontSize = 10);
        void SetText(const std::string& text);
        void SetTextSize(unsigned int size);

    private:
        virtual void Draw(sf::RenderWindow& windowRef) override;
        virtual void LocationUpdated(const sf::Vector2f &newLocation) override;
        virtual void RotationUpdated(float newRotation) override;
        sf::Text m_Text;
        shared<sf::Font> m_Font;
    };
}

#endif //WIDGETTEXT_H
