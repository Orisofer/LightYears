//
// Created by Ori Sofer on 12/07/2025.
//

#ifndef UFOSTAGE_H
#define UFOSTAGE_H

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class UFOStage : public GameStage
    {
    public:
        UFOStage(World* owningWorld);
        virtual void StartStage() override;
    private:
        virtual void StageFinished() override;
        void SpawnUFO();
        sf::Vector2f GetRandomSpawnLoc() const;

        TimerHandler m_SpawnTimer;

        float m_SpawnInterval;
        float m_UFOSpeed;
        int m_SpawnAmount;
        int m_CurrentSpawnAmount;
    };
}

#endif //UFOSTAGE_H
