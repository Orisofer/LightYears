//
// Created by Ori Sofer on 11/07/2025.
//

#ifndef HEXAGONSTAGE_H
#define HEXAGONSTAGE_H

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class HexagonStage : public GameStage
    {
    public:
        HexagonStage(World* owningWorld);
        virtual void StartStage() override;
    private:
        virtual void StageFinished() override;
        void SpawnHexagon();

        TimerHandler m_SpawnTimer;

        sf::Vector2f m_LeftSpawnLocation;
        sf::Vector2f m_MidSpawnLocation;
        sf::Vector2f m_RightSpawnLocation;

        float m_SpawnInterval;
        float m_SideSpawnOffset;
        int m_SpawnGroupAmount;
        int m_CurrentSpawnCount;
    };
}

#endif //HEXAGONSTAGE_H
