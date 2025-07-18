//
// Created by Ori Sofer on 12/07/2025.
//

#include "weapon/FrontalWiperShooter.h"

namespace ly
{
    FrontalWiperShooter::FrontalWiperShooter(Actor *owningActor, float cooldownTime, const sf::Vector2f &localOffset)
        : Shooter(owningActor),
    m_ShooterLeft(owningActor, cooldownTime, localOffset + sf::Vector2f(-45.f,00.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_ShooterMid01(owningActor, cooldownTime, localOffset + sf::Vector2f(-25.f,10.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_ShooterMid02(owningActor, cooldownTime, localOffset + sf::Vector2f(25.f,10.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_ShooterRight(owningActor, cooldownTime, localOffset + sf::Vector2f(45.f,00.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_MaxLevelShooterRight(owningActor, cooldownTime, localOffset + sf::Vector2f(80.f,-55.f), 90.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_MaxLevelShooterLeft(owningActor, cooldownTime, localOffset + sf::Vector2f(-80.f,-55.f), -90.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png")
    {

    }

    void FrontalWiperShooter::LevelUp(int amount)
    {
        Shooter::LevelUp(amount);

        m_ShooterLeft.LevelUp(amount);
        m_ShooterMid01.LevelUp(amount);
        m_ShooterMid02.LevelUp(amount);
        m_ShooterRight.LevelUp(amount);

        m_MaxLevelShooterRight.LevelUp(amount);
        m_MaxLevelShooterLeft.LevelUp(amount);
    }

    void FrontalWiperShooter::ShootImpl()
    {
        m_ShooterLeft.Shoot();
        m_ShooterMid01.Shoot();
        m_ShooterMid02.Shoot();
        m_ShooterRight.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            m_MaxLevelShooterRight.Shoot();
            m_MaxLevelShooterLeft.Shoot();
        }
    }
}
