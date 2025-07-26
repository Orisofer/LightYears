//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD() :
    m_FpsCounter("Frame rate:")
    {

    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        m_FpsCounter.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        HUD::Tick(deltaTime);

        int frameRate = int(1 / deltaTime);
        std::string frameRateString = "Frame Rate: " + std::to_string(frameRate);
        m_FpsCounter.SetText(frameRateString);
    }
}
