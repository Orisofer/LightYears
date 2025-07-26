//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD() :
    m_FpsCounter("Frame rate:"),
    m_HealthBar()
    {

    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        float healthBarPosX = 10.f;

        float halfBarYSize = m_HealthBar.GetBarSize().y / 2.f;
        float padding = 15.f;

        float healthBarPosY = windowRef.getSize().y - halfBarYSize - padding;
        m_HealthBar.SetLocation(sf::Vector2f(healthBarPosX, healthBarPosY));
        m_HealthBar.UpdateValue(100.f, 200.f);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        m_FpsCounter.NativeDraw(windowRef);
        m_HealthBar.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        HUD::Tick(deltaTime);

        int frameRate = int(1 / deltaTime);
        std::string frameRateString = "Frame Rate: " + std::to_string(frameRate);
        m_FpsCounter.SetText(frameRateString);
    }
}
