//
// Created by Ori Sofer on 07/06/2025.
//

#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly
{
    GameStage::GameStage(World *world) :
    m_World(world),
    m_StageFinished(false)
    {
    }

    const World * GameStage::GetWorld() const
    {
        return m_World;
    }

    World * GameStage::GetWorld()
    {
        return m_World;
    }

    void GameStage::StartStage()
    {
        LOG("StartStage");
    }

    void GameStage::TickStage(float deltaTime)
    {
    }

    void GameStage::FinishStage()
    {
        m_StageFinished = true;
        StageFinished();
        OnStageFinished.Broadcast();
    }

    bool GameStage::IsStageFinished() const
    {
        return m_StageFinished;
    }

    void GameStage::StageFinished()
    {
        LOG("FinishStage");
    }
}
