//
// Created by Ori Sofer on 05/07/2025.
//

#ifndef TWINBLADESTAGE_H
#define TWINBLADESTAGE_H

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World* owningWorld);
        virtual void StartStage() override;
    private:
        TimerHandler m_SpawnTimerHandler;

        sf::Vector2f m_LeftSpawnLocation;
        sf::Vector2f m_RightSpawnLocation;
        sf::Vector2f m_SpawnLocation;

        float m_SpawningInterval;
        float m_SwitchInterval;
        float m_SpawnDistanceToCenter;

        int m_SpawnAmount;
        int m_CurrentSpawnCount;

        virtual void StageFinished() override;
        void SpawnTwinBlade();
        void SwitchSpawnLocation();
    };
}

#endif //TWINBLADESTAGE_H
