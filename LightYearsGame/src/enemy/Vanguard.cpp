//
// Created by Ori Sofer on 03/05/2025.
//

#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Vanguard::Vanguard(World *owningWorld, const std::string &texturePath, const sf::Vector2f& velocity) :
    EnemySpaceship(owningWorld, texturePath),
    m_BulletShooter(new BulletShooter(this, 1.8f, {0.f, 50.f}, 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"))
    {
        SetVelocity(velocity);
        SetRotation(180.f);
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
