//
// Created by Ori Sofer on 01/08/2025.
//

#ifndef WIDGETBUTTON_H
#define WIDGETBUTTON_H

#include "framework/Delegate.h"
#include "widgets/Widget.h"
#include "widgets/WidgetText.h"

namespace ly
{
    class WidgetButton : public Widget
    {
    public:
        WidgetButton(const std::string& text = "button",
            const std::string& texturePath = "/SpaceShooterRedux/PNG/UI/buttonGreen.png",
            const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
            sf::Color colorDefault = sf::Color(200,200,200,255),
            sf::Color colorClicked = sf::Color(45,150,45,255),
            sf::Color colorHover = sf::Color(235,235,235,255),
            sf::Color colorText = sf::Color(20,20,20,255));
        virtual sf::FloatRect GetBounds() const override;
        virtual bool HandleEvent(const sf::Event &event) override;
        Delegate<> OnClick;

    private:
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void LocationUpdated(const sf::Vector2f &newLocation) override;
        virtual void RotationUpdated(float newRotation) override;

        void InitSprite();
        void InitText(const std::string& text);
        void SetColor(const sf::Color& color);
        void CenterText();
        void ButtonUp();
        void ButtonDown();
        void MouseHover();

    private:
        sf::Sprite m_Sprite;
        sf::Text m_Text;
        shared<sf::Texture> m_Texture;
        shared<sf::Font> m_Font;

        sf::Color m_ColorDefault;
        sf::Color m_ColorClicked;
        sf::Color m_ColorHover;
        sf::Color m_ColorText;

        bool m_IsDown;
    };
}

#endif //WIDGETBUTTON_H
