//
// Created by Ori Sofer on 09/07/2025.
//

#ifndef HEXAGON_H
#define HEXAGON_H
#include "EnemySpaceship.h"

namespace ly
{
    class BulletShooter;

    class Hexagon : public EnemySpaceship
    {
    public:
        Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed4.png",
            const sf::Vector2f& velocity = {0.f, 50.f});
        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;

        unique<BulletShooter> m_BulletShooter01;
        unique<BulletShooter> m_BulletShooter02;
        unique<BulletShooter> m_BulletShooter03;
        unique<BulletShooter> m_BulletShooter04;
        unique<BulletShooter> m_BulletShooter05;
        unique<BulletShooter> m_BulletShooter06;
    };
}

#endif //HEXAGON_H
