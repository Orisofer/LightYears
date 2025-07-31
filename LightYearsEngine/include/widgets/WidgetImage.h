//
// Created by Ori Sofer on 31/07/2025.
//

#ifndef WIDGETIMAGE_H
#define WIDGETIMAGE_H

#include "Widget.h"

namespace ly
{
    class WidgetImage : public Widget
    {
    public:
        WidgetImage(const std::string& filePath);
        virtual sf::FloatRect GetBounds() const override;
        void SetImage(const shared<sf::Texture>& texture);
        void SetSizeMultiplier(float multiplier);

    private:
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
        virtual void RotationUpdated(float newRotation) override;
        void LoadTexture(const std::string& path);
        shared<sf::Texture> m_Texture;
        sf::Sprite m_Sprite;
    };
}

#endif //WIDGETIMAGE_H
