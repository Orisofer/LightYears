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
        "SpaceShooterRedux/PNG/Lasers/laserRed08.png"),
    m_ThreeWayShooter(this, 4.f, sf::Vector2f{100.f, 0.f}, 180.f),
    m_FrontalWiperShooterLeft(this, 5.f, sf::Vector2f{100.f, -120.f}, 180.f),
    m_FrontalWiperShooterRight(this, 5.f, sf::Vector2f{100.f, 100.f}, 180.f)
    {

    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();

        SetVelocity({m_Speed, 0.f});
        SetRewardSpawnWeight(-1.f);

        HealthComponent& healthComp = GetHealthComponent();
        healthComp.SetHealth(3000.f,3000.f);

        healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);

        SetStage(1);
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        ShootBaseShooters();
        ShootFrontalWiperShooters();
        ShootThreeWayShooter();
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
        }
    }

    void Boss::ShootBaseShooters()
    {
        m_BaseShooterLeft.Shoot();
        m_BaseShooterRight.Shoot();
    }

    void Boss::ShootThreeWayShooter()
    {
        m_ThreeWayShooter.Shoot();
    }

    void Boss::ShootFrontalWiperShooters()
    {
        m_FrontalWiperShooterLeft.Shoot();
        m_FrontalWiperShooterRight.Shoot();
    }

    void Boss::HealthChanged(float amount, float currentHealth, float maxHealth)
    {
        float percentLeft = currentHealth / maxHealth;

        if (percentLeft < 0.7f && percentLeft > 0.5f)
        {
            SetStage(2);
        }
        else if (percentLeft < 0.5f && percentLeft > 0.2f)
        {
            SetStage(3);
        }
        else if (percentLeft < 0.2f)
        {
            SetStage(4);
        }
    }

    void Boss::SetStage(int stage)
    {
        m_Stage = stage;

        m_BaseShooterLeft.SetCurrentLevel(m_Stage);
        m_BaseShooterRight.SetCurrentLevel(m_Stage);
        m_ThreeWayShooter.SetCurrentLevel(m_Stage);
        m_FrontalWiperShooterLeft.SetCurrentLevel(m_Stage);
        m_FrontalWiperShooterRight.SetCurrentLevel(m_Stage);
    }
}
