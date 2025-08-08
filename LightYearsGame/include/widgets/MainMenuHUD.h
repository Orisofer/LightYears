//
// Created by Ori Sofer on 08/08/2025.
//

#ifndef MAINMENUHUD_H
#define MAINMENUHUD_H

#include "framework/Actor.h"
#include "widgets/HUD.h"
#include "widgets/WidgetImage.h"
#include "widgets/WidgetText.h"
#include "widgets/WidgetValueGauge.h"
#include "widgets/WidgetButton.h"

namespace ly
{
    class MainMenuHUD : public HUD
    {
    public:
        MainMenuHUD();

        virtual void Init(const sf::RenderWindow &windowRef) override;
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual bool HandleEvent(const sf::Event &event) override;

        Delegate<> OnStartClicked;
        Delegate<> OnQuitClicked;

    private:
        void OnStartButtonClicked();
        void OnQuitButtonClicked();
        WidgetText m_TitleText;
        WidgetButton m_ButtonStart;
        WidgetButton m_ButtonQuit;

    };
}

#endif //MAINMENUHUD_H
