//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/HUD.h"

namespace ly
{
    HUD::HUD() :
    m_HasInit(false)
    {

    }

    void HUD::NativeInit(const sf::RenderWindow &windowRef)
    {
        if (!m_HasInit)
        {
            m_HasInit = true;
            Init(windowRef);
        }
    }

    void HUD::Tick(float deltaTime)
    {
        // no-op
    }

    void HUD::Init(const sf::RenderWindow &windowRef)
    {

    }

    bool HUD::HasInit()
    {
        return m_HasInit;
    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }
}
