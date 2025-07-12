//
// Created by Ori Sofer on 12/07/2025.
//

#include "enemy/UFOStage.h"
#include "enemy/UFO.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    UFOStage::UFOStage(World* owningWorld)
        : GameStage(owningWorld),
    m_SpawnInterval(2.f),
    m_SpawnAmount(10),
    m_CurrentSpawnAmount(0),
    m_UFOSpeed(200.f)
    {

    }

    void UFOStage::StartStage()
    {
        GameStage::StartStage();

        m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, m_SpawnInterval, true);
    }

    void UFOStage::StageFinished()
    {
        GameStage::StageFinished();

        TimerManager::Get().ClearTimer(m_SpawnTimer);
    }

    void UFOStage::SpawnUFO()
    {
        if (m_CurrentSpawnAmount <= m_SpawnAmount)
        {
            m_CurrentSpawnAmount++;

            sf::Vector2f spawnLoc = GetRandomSpawnLoc();
            sf::Vector2u windowSize = GetWorld()->GetWindowSize();

            sf::Vector2f centerWorld{windowSize.x / 2.f, windowSize.y / 2.f};
            sf::Vector2f dirToCenter = centerWorld - spawnLoc;

            Normalize(dirToCenter);

            sf::Vector2f ufoVelocity = dirToCenter * m_UFOSpeed;

            weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(ufoVelocity);

            newUFO.lock()->SetLocation(spawnLoc);
        }
        else
        {
            FinishStage();
        }
    }

    sf::Vector2f UFOStage::GetRandomSpawnLoc() const
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

        return sf::Vector2f(spawnLocX, spawnLocY);
    }
}
