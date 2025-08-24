//
// Created by Ori Sofer on 22/08/2025.
//

#include "enemy/Boss.h"
#include "framework/World.h"

namespace ly
{
    Boss::Boss(World *owningWorld, const std::string& texturePath) :
    EnemySpaceship(owningWorld, texturePath),
    m_Speed(100.f),
    m_SwitchDistanceToEdge(100.f),
    m_BaseShooterLeft(this, 2.0f, sf::Vector2f{50.f, -50.f}, 180.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png"),
    m_BaseShooterRight(this, 2.0f, sf::Vector2f{-50.f, -50.f}, 180.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png")
    {

    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        ShootBaseShooters();
        CheckMove();
    }

    void Boss::CheckMove()
    {
        sf::Vector2f bossLocation = GetLocation();
        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        if (bossLocation.x > windowSize.x - m_SwitchDistanceToEdge)
        {
            SetVelocity({-m_Speed, 0.f});
            return;
        }

        if (bossLocation.x < m_SwitchDistanceToEdge)
        {
            SetVelocity({m_Speed, 0.f});
            return;
        }
    }

    void Boss::ShootBaseShooters()
    {
        m_BaseShooterLeft.Shoot();
        m_BaseShooterRight.Shoot();
    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();

        SetVelocity({m_Speed, 0.f});
        SetRewardSpawnWeight(-1.f);

        HealthComponent& healthComp = GetHealthComponent();
        healthComp.SetHealth(3000.f,3000.f);
    }
}
