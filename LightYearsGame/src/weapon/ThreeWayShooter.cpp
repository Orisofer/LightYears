//
// Created by Ori Sofer on 12/07/2025.
//

#include "weapon/ThreeWayShooter.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(Actor *owningActor, float cooldownTime, const sf::Vector2f &localOffset)
        : Shooter(owningActor),
    m_ShooterLeft(owningActor, cooldownTime, localOffset + sf::Vector2f(-10.f,10.f), -25.f,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
    m_ShooterMid(owningActor, cooldownTime, localOffset, 00.f,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
    m_ShooterRight(owningActor, cooldownTime, localOffset + sf::Vector2f(10.f,10.f), 25.f,
        "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")
    {

    }

    void ThreeWayShooter::ShootImpl()
    {
        m_ShooterLeft.Shoot();
        m_ShooterMid.Shoot();
        m_ShooterRight.Shoot();
    }
}
