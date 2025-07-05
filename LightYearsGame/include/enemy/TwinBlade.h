//
// Created by Ori Sofer on 05/07/2025.
//

#ifndef TWINBLADE_H
#define TWINBLADE_H
#include "enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class TwinBlade : public EnemySpaceship
    {
    public:
        TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png",
            const sf::Vector2f& velocity = {0.f, 120.f});
        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;
        unique<BulletShooter> m_BulletShooterLeft;
        unique<BulletShooter> m_BulletShooterRight;
    };
}


#endif //TWINBLADE_H
