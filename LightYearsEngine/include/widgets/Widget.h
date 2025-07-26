//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ly
{
    class Widget : public Object
    {
    public:
        void NativeDraw(sf::RenderWindow& windowRef);
        virtual bool HandleEvent(const sf::Event& event);
        void SetLocation(const sf::Vector2f& newLocation);
        void SetRotation(float newRotation);
        void SetVisibility(bool visible);
        sf::Vector2f GetLocation() const;
        float GetRotation() const;
        bool GetVisibility() const;

    protected:
        Widget();

    private:
        virtual void Draw(sf::RenderWindow& windowRef) = 0;
        virtual void LocationUpdated(const sf::Vector2f& newLocation) = 0;
        virtual void RotationUpdated(float newRotation) = 0;
        sf::Transformable m_WidgetTransform;
        bool m_IsVisible;
    };
}

#endif //WIDGET_H
