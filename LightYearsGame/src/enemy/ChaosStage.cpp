//
// Created by Ori Sofer on 15/08/2025.
//

#include "framework/MathUtility.h"
#include "framework/World.h"
#include "enemy/ChaosStage.h"
#include "enemy/UFO.h"
#include "enemy/Hexagon.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    ChaosStage::ChaosStage(World *owningWorld) :
    GameStage(owningWorld),
    m_SpawningInterval(4.f),
    m_MinSpawnInterval(.8f),
    m_SpawnIntervalDecrement(0.5),
    m_SpawnIntervalDecrementInterval(5.f),
    m_StageDuration(60.f)
    {

    }

    void ChaosStage::StartStage()
    {
        GameStage::StartStage();

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard,
            m_SpawningInterval, false);

        m_DifficultTimerHandler = TimerManager::Get().SetTimer(GetWeakRef(),
            &ChaosStage::IncreaseDifficulty, m_SpawnIntervalDecrementInterval, true);

        TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, m_StageDuration, false);
    }

    void ChaosStage::StageFinished()
    {
        GameStage::StageFinished();

        TimerManager::Get().ClearTimer(m_DifficultTimerHandler);
        TimerManager::Get().ClearTimer(m_SpawnTimer);
    }

    void ChaosStage::SpawnVanguard()
    {
        weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();

        newVanguard.lock()->SetLocation(GetRandomSpawnLocationTop());

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade,
            m_SpawningInterval, false);
    }

    void ChaosStage::SpawnTwinBlade()
    {
        weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();

        newTwinBlade.lock()->SetLocation(GetRandomSpawnLocationTop());

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon,
            m_SpawningInterval, false);
    }

    void ChaosStage::SpawnHexagon()
    {
        weak<Hexagon> newTwinBlade = GetWorld()->SpawnActor<Hexagon>();

        newTwinBlade.lock()->SetLocation(GetRandomSpawnLocationTop());

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO,
            m_SpawningInterval, false);
    }

    void ChaosStage::SpawnUFO()
    {
        sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();
        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        sf::Vector2f centerWorld{windowSize.x / 2.f, windowSize.y / 2.f};
        sf::Vector2f dirToCenter = centerWorld - spawnLoc;

        Normalize(dirToCenter);

        sf::Vector2f ufoVelocity = dirToCenter * 200.f;

        weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(ufoVelocity);

        newUFO.lock()->SetLocation(spawnLoc);

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard,
            m_SpawningInterval, false);
    }

    void ChaosStage::IncreaseDifficulty()
    {
        m_SpawningInterval -= m_SpawnIntervalDecrement;

        if (m_SpawningInterval < m_MinSpawnInterval)
        {
            m_SpawningInterval = m_MinSpawnInterval;
        }
    }

    void ChaosStage::StageDurationReached()
    {
        FinishStage();
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
    {
        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        float randomLocationX = RandomRange(100.f, windowSize.x - 100.f);
        float locationY = -100.f;

        return {randomLocationX, locationY};
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
    {
        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        float spawnLeft = RandomRange(-1.f,1.f);
        float spawnLocX = 0;

        if (spawnLeft > 0)
        {
            spawnLocX = windowSize.x + 100.f;
        }
        else
        {
            spawnLocX = -100.f;
        }

        float spawnLocY = RandomRange(0,windowSize.y);

        return {spawnLocX, spawnLocY};
    }
}
