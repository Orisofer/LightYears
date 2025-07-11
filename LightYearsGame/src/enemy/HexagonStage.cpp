//
// Created by Ori Sofer on 11/07/2025.
//

#include "framework/World.h"
#include "enemy/HexagonStage.h"
#include "enemy/Hexagon.h"

namespace ly
{
    HexagonStage::HexagonStage(World *owningWorld)
        : GameStage(owningWorld),
    m_SpawnInterval(5.f),
    m_SideSpawnOffset(80.f),
    m_SpawnGroupAmount(5),
    m_CurrentSpawnCount(0)
    {
        m_MidSpawnLocation = (sf::Vector2f(owningWorld->GetWindowSize().x / 2, -100.f));
        m_RightSpawnLocation = (sf::Vector2f(owningWorld->GetWindowSize().x / 2 + m_SideSpawnOffset, -100.f - m_SideSpawnOffset));
        m_LeftSpawnLocation = (sf::Vector2f(owningWorld->GetWindowSize().x / 2 - m_SideSpawnOffset, -100.f - m_SideSpawnOffset));
    }

    void HexagonStage::StartStage()
    {
        GameStage::StartStage();

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, m_SpawnInterval, true);
    }

    void HexagonStage::StageFinished()
    {
        GameStage::StageFinished();

        TimerManager::Get().ClearTimer(m_SpawnTimer);
    }

    void HexagonStage::SpawnHexagon()
    {
        weak<Hexagon> hexagon = GetWorld()->SpawnActor<Hexagon>();
        hexagon.lock()->SetLocation(m_MidSpawnLocation);

        hexagon = GetWorld()->SpawnActor<Hexagon>();
        hexagon.lock()->SetLocation(m_LeftSpawnLocation);

        hexagon = GetWorld()->SpawnActor<Hexagon>();
        hexagon.lock()->SetLocation(m_RightSpawnLocation);

        if (++m_CurrentSpawnCount == m_SpawnGroupAmount)
        {
            FinishStage();
        }
    }
}
