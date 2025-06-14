//
// Created by Ori Sofer on 13/06/2025.
//

#ifndef VANGUARDSTAGE_H
#define VANGUARDSTAGE_H

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class VanguardStage : public GameStage
    {
    public:
        VanguardStage(World* world);
        virtual void StartStage() override;
    private:
        TimerHandler m_SpawnTimerHandler;
        TimerHandler m_SwitchTimerHandler;

        sf::Vector2f m_LeftSpawnLocation;
        sf::Vector2f m_RightSpawnLocation;
        sf::Vector2f m_SpawnLocation;

        float m_SpawningInterval;
        float m_SwitchInterval;
        float m_SpawnDistanceToEdge;

        int m_RowsToSpawn;
        int m_RowsSpawnCount;
        int m_VanguardsPerRow;
        int m_CurrentRowVanguardCount;

        virtual void StageFinished() override;
        void SpawnVanguard();
        void SwitchRow();
    };
}

#endif //VANGUARDSTAGE_H
