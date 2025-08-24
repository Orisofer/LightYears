//
// Created by Ori Sofer on 22/08/2025.
//

#ifndef BOSS_H
#define BOSS_H

#include "enemy/EnemySpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiperShooter.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* owningWorld, const std::string& texturePath = "/SpaceShooterRedux/PNG/Enemies/enemyBoss.png");
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        void CheckMove();
        void ShootBaseShooters();
        float m_Speed;
        float m_SwitchDistanceToEdge;

        BulletShooter m_BaseShooterLeft;
        BulletShooter m_BaseShooterRight;

    };

}

#endif //BOSS_H
