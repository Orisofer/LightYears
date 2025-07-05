//
// Created by Ori Sofer on 05/07/2025.
//

#include "enemy/TwinBladeStage.h"

#include "enemy/TwinBlade.h"
#include "framework/World.h"

namespace ly
{
    TwinBladeStage::TwinBladeStage(World *owningWorld)
        : GameStage(owningWorld),
    m_SpawningInterval(1.5f),
    m_SpawnDistanceToCenter(100.0f),
    m_SpawnAmount(10),
    m_CurrentSpawnCount(0)
    {

    }

    void TwinBladeStage::StartStage()
    {
        GameStage::StartStage();

        m_LeftSpawnLocation = sf::Vector2f((GetWorld()->GetWindowSize().x / 2) - m_SpawnDistanceToCenter, -100.f);
        m_RightSpawnLocation = sf::Vector2f((GetWorld()->GetWindowSize().x / 2) + m_SpawnDistanceToCenter, -100.f);
        m_SpawnLocation = m_LeftSpawnLocation;

        m_SpawnTimerHandler = TimerManager::Get().SetTimer(GetWeakRef(),
        &TwinBladeStage::SpawnTwinBlade, m_SpawningInterval, true);
    }

    void TwinBladeStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(m_SpawnTimerHandler);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        if (m_CurrentSpawnCount < m_SpawnAmount)
        {
            weak<TwinBlade> twinBlade = GetWorld()->SpawnActor<TwinBlade>();
            twinBlade.lock()->SetLocation(m_SpawnLocation);
            m_CurrentSpawnCount++;

            SwitchSpawnLocation();
        }
        else
        {
            FinishStage();
        }
    }

    void TwinBladeStage::SwitchSpawnLocation()
    {
        if (m_SpawnLocation == m_LeftSpawnLocation)
        {
            m_SpawnLocation = m_RightSpawnLocation;
        }
        else
        {
            m_SpawnLocation = m_LeftSpawnLocation;
        }
    }
}
