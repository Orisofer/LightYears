//
// Created by Ori Sofer on 22/08/2025.
//

#ifndef BOSS_H
#define BOSS_H

#include "enemy/EnemySpaceship.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* owningWorld, const std::string& texturePath = "/SpaceShooterRedux/PNG/Enemies/enemyBoss.png");
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        float m_Speed;
        float m_SwitchDistanceToEdge;

    };

}

#endif //BOSS_H
