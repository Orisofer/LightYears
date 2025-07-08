//
// Created by Ori Sofer on 08/07/2025.
//

#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    WaitStage::WaitStage(World *world, float waitTime) :
    GameStage(world),
    m_WaitTime(waitTime)
    {

    }

    void WaitStage::StartStage()
    {
        m_WaitTimeHandler = TimerManager::Get().SetTimer(GetWeakRef(), &GameStage::FinishStage, m_WaitTime, false);
    }
}
