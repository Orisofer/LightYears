//
// Created by Ori Sofer on 15/08/2025.
//

#ifndef CHAOSSTAGE_H
#define CHAOSSTAGE_H

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World* owningWorld);
        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;

        void SpawnVanguard();
        void SpawnTwinBlade();
        void SpawnHexagon();
        void SpawnUFO();
        void IncreaseDifficulty();
        void StageDurationReached();

        sf::Vector2f GetRandomSpawnLocationTop() const;
        sf::Vector2f GetRandomSpawnLocationSide() const;

        float m_SpawningInterval;
        float m_MinSpawnInterval;
        float m_SpawnIntervalDecrement;
        float m_SpawnIntervalDecrementInterval;
        float m_StageDuration;

        TimerHandler m_DifficultTimerHandler;
        TimerHandler m_SpawnTimer;
    };
}

#endif //CHAOSSTAGE_H
