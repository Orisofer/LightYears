//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
#include "widgets/WidgetText.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void Tick(float deltaTime) override;

    private:
        WidgetText m_FpsCounter;
        float m_PreviousFrameTime;
    };
}


#endif //GAMEPLAYHUD_H
