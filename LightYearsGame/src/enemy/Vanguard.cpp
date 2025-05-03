//
// Created by Ori Sofer on 03/05/2025.
//

#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Vanguard::Vanguard(World *owningWorld, const std::string &texturePath, const sf::Vector2f& velocity) :
    EnemySpaceship(owningWorld, texturePath),
    m_BulletShooter(new BulletShooter(this, 1.8f))
    {
        SetVelocity(velocity);
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        Shoot();
    }

    void Vanguard::Shoot()
    {
        m_BulletShooter->Shoot();
    }
}
