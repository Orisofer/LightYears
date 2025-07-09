//
// Created by Ori Sofer on 09/07/2025.
//

#include "enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Hexagon::Hexagon(World* owningWorld, const std::string& texturePath,const sf::Vector2f& velocity) :
    EnemySpaceship(owningWorld, texturePath),
    m_BulletShooter01{new BulletShooter(this, 1.02f, sf::Vector2f{00.f, -50.f}, 180.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png"),},
    m_BulletShooter02{new BulletShooter(this, 1.01f, sf::Vector2f{40.f, -25.f}, 120.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")},
    m_BulletShooter03{new BulletShooter(this, 1.03f, sf::Vector2f{-40.f, -25.f}, -120.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")},
    m_BulletShooter04{new BulletShooter(this, 1.05f, sf::Vector2f{00.f, 50.f}, 00.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")},
    m_BulletShooter05{new BulletShooter(this, 1.06f, sf::Vector2f{40.f, 25.f}, 60.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")},
    m_BulletShooter06{new BulletShooter(this, 1.04f, sf::Vector2f{-40.f, 25.f}, -60.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")}
    {
        SetVelocity(velocity);
    }

    void Hexagon::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        Shoot();
    }

    void Hexagon::Shoot()
    {
        m_BulletShooter01->Shoot();
        m_BulletShooter02->Shoot();
        m_BulletShooter03->Shoot();
        m_BulletShooter04->Shoot();
        m_BulletShooter05->Shoot();
        m_BulletShooter06->Shoot();
    }
}
