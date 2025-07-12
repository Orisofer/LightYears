//
// Created by Ori Sofer on 12/07/2025.
//

#include "weapon/FrontalWiperShooter.h"

namespace ly
{
    FrontalWiperShooter::FrontalWiperShooter(Actor *owningActor, float cooldownTime, const sf::Vector2f &localOffset)
        : Shooter(owningActor),
    m_ShooterLeft(owningActor, cooldownTime, localOffset + sf::Vector2f(-15.f,10.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_ShooterMid(owningActor, cooldownTime, localOffset, 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
    m_ShooterRight(owningActor, cooldownTime, localOffset + sf::Vector2f(15.f,10.f), 0.f,
        "SpaceShooterRedux/PNG/Lasers/laserRed01.png")
    {

    }

    void FrontalWiperShooter::ShootImpl()
    {
        m_ShooterLeft.Shoot();
        m_ShooterMid.Shoot();
        m_ShooterRight.Shoot();
    }
}
