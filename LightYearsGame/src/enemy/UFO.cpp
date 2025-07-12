//
// Created by Ori Sofer on 12/07/2025.
//

#include "enemy/UFO.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    UFO::UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
        : EnemySpaceship(owningWorld, texturePath),
    m_Shooter01(new BulletShooter(this, .5f, sf::Vector2f(0.f,0.f), -60,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")),
    m_Shooter02(new BulletShooter(this, .5f, sf::Vector2f(0.f,0.f), 60,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")),
    m_Shooter03(new BulletShooter(this, .5f, sf::Vector2f(0.f,0.f), 180,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")),
    m_RotationSpeed(rotationSpeed)
    {
        SetVelocity(velocity);
        SetRotation(90.f);
    }

    void UFO::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        Shoot();
        AddActorRotationOffset(m_RotationSpeed * deltaTime);
    }

    void UFO::Shoot()
    {
        m_Shooter01->Shoot();
        m_Shooter02->Shoot();
        m_Shooter03->Shoot();
    }
}
