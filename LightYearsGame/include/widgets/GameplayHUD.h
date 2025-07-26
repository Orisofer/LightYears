//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
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
        WidgetText m_FpsCounter;
        WidgetValueGauge m_HealthBar;
    };
}


#endif //GAMEPLAYHUD_H
