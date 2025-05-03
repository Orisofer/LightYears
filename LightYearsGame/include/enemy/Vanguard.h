//
// Created by Ori Sofer on 03/05/2025.
//

#ifndef VANGUARD_H
#define VANGUARD_H

#include "EnemySpaceship.h"

namespace ly
{
    class BulletShooter;

    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen2.png",
            const sf::Vector2f& velocity = {0.f, 50.f});
        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;
        unique<BulletShooter> m_BulletShooter;
    };
}

#endif //VANGUARD_H
