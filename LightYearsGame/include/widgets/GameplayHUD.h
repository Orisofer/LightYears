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
        void OnPlayerScoreChanged(unsigned int score);
        void OnPlayerLifeChanged(int life);
        void RegisterPlayerData();
        void OnPlayerLifeExhausted();
        void RefreshHealthBar();
        void RefreshPlayerScore(unsigned int score);
        void RefreshPlayerLives(int lives);
        WidgetText m_FpsCounter;
        WidgetText m_LifeCounter;
        WidgetText m_ScoreCounter;
        WidgetValueGauge m_HealthBar;
        WidgetImage m_PlayerLiveIcon;
        WidgetImage m_PlayerScoreIcon;
    };
}


#endif //GAMEPLAYHUD_H
