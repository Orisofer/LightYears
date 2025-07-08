//
// Created by Ori Sofer on 13/06/2025.
//

#include "enemy/VanguardStage.h"
#include "framework/World.h"
#include "enemy/Vanguard.h"

namespace ly
{
    VanguardStage::VanguardStage(World *world) :
    GameStage(world),
    m_SpawningInterval(1.5f),
    m_SwitchInterval(2.f),
    m_SpawnDistanceToEdge(100.f),
    m_LeftSpawnLocation(0.f, 0.f),
    m_RightSpawnLocation(0.f, 0.f),
    m_SpawnLocation(0.f, 0.f),
    m_RowsToSpawn(2),
    m_CurrentRowVanguardCount(0),
    m_VanguardsPerRow(5),
    m_RowsSpawnCount(0)
    {

    }

    void VanguardStage::StartStage()
    {
        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        m_LeftSpawnLocation = sf::Vector2f(m_SpawnDistanceToEdge, -100.f);
        m_RightSpawnLocation = sf::Vector2f(windowSize.x - m_SpawnDistanceToEdge, 0.f);

        SwitchRow();
    }

    void VanguardStage::StageFinished()
    {
        GameStage::StageFinished();

        TimerManager::Get().ClearTimer(m_SwitchTimerHandler);
        TimerManager::Get().ClearTimer(m_SpawnTimerHandler);
    }

    void VanguardStage::SpawnVanguard()
    {
        if (m_CurrentRowVanguardCount > m_VanguardsPerRow)
        {
            TimerManager::Get().ClearTimer(m_SpawnTimerHandler);
            m_SwitchTimerHandler = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, m_SwitchInterval, false);

            m_CurrentRowVanguardCount = 0;
        }

        weak<Vanguard> vanguard = GetWorld()->SpawnActor<Vanguard>();
        vanguard.lock()->SetLocation(m_SpawnLocation);
        m_CurrentRowVanguardCount++;
    }

    void VanguardStage::SwitchRow()
    {
        if (m_RowsSpawnCount == m_RowsToSpawn)
        {
            FinishStage();
            return;
        }

        m_SpawnLocation = m_SpawnLocation == m_LeftSpawnLocation ? m_RightSpawnLocation : m_LeftSpawnLocation;

        m_SpawnTimerHandler = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, m_SpawningInterval, true);

        m_RowsSpawnCount++;
    }
}
