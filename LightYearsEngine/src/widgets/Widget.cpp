//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/Widget.h"

namespace ly
{
    Widget::Widget() :
    m_IsVisible(true),
    m_WidgetTransform()
    {
    }

    void Widget::NativeDraw(sf::RenderWindow &windowRef)
    {
        if (m_IsVisible)
        {
            Draw(windowRef);
        }
    }

    void Widget::Draw(sf::RenderWindow& windowRef)
    {
        // abstract
    }

    void Widget::LocationUpdated(const sf::Vector2f &newLocation)
    {
        // abstract
    }

    void Widget::RotationUpdated(float newRotation)
    {
        // abstract
    }

    bool Widget::HandleEvent(const sf::Event &event)
    {
        // abstract
        return true;
    }

    void Widget::SetLocation(const sf::Vector2f &newLocation)
    {
        m_WidgetTransform.setPosition(newLocation);

        LocationUpdated(newLocation);
    }

    void Widget::SetRotation(float newRotation)
    {
        m_WidgetTransform.setRotation(newRotation);

        RotationUpdated(newRotation);
    }

    void Widget::SetVisibility(bool visible)
    {
        m_IsVisible = visible;
    }

    sf::Vector2f Widget::GetLocation() const
    {
        return m_WidgetTransform.getPosition();
    }

    float Widget::GetRotation() const
    {
        return m_WidgetTransform.getRotation();
    }

    bool Widget::GetVisibility() const
    {
        return m_IsVisible;
    }

    sf::FloatRect Widget::GetBounds() const
    {
        return sf::FloatRect();
    }

    sf::Vector2f Widget::GetCenter() const
    {
        sf::FloatRect bounds = GetBounds();
        sf::Vector2f center = {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
        return center;
    }
}
