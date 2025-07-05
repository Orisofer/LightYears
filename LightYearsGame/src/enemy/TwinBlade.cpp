//
// Created by Ori Sofer on 05/07/2025.
//

#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    TwinBlade::TwinBlade(World *owningWorld, const std::string &texturePath, const sf::Vector2f &velocity)
        : EnemySpaceship(owningWorld, texturePath),
    m_BulletShooterLeft(new BulletShooter(this, 1.0f, {-20.f, 50.f}, 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png")),
    m_BulletShooterRight(new BulletShooter(this, 1.0f, {20.f, 50.f}, 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"))
    {
        SetVelocity(velocity);
        SetRotation(180.f);
    }

    void TwinBlade::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        Shoot();
    }

    void TwinBlade::Shoot()
    {
        m_BulletShooterLeft->Shoot();
        m_BulletShooterRight->Shoot();
    }
}
