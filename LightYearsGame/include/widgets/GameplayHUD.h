//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "framework/Actor.h"
#include "widgets/HUD.h"
#include "widgets/WidgetImage.h"
#include "widgets/WidgetText.h"
#include "widgets/WidgetValueGauge.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void Init(const sf::RenderWindow &windowRef) override;
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void Tick(float deltaTime) override;


    private:
        void OnPlayerHealthUpdated(float amt, float health, float maxHealth);
        void OnPlayerSpaceshipDestroyed(Actor* spaceship);
        void RefreshHealthBar();
        WidgetText m_FpsCounter;
        WidgetValueGauge m_HealthBar;
        WidgetImage m_PlayerLiveIcon;
    };
}


#endif //GAMEPLAYHUD_H
