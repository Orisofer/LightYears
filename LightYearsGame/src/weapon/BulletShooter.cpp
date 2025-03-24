//
// Created by Ori Sofer on 24/03/2025.
//

#include "weapon/BulletShooter.h"


namespace ly
{
    BulletShooter::BulletShooter(Actor *owner, float coolDownTime) : Shooter{owner},
    m_CooldownClock{},
    m_CooldownTime{coolDownTime}
    {

    }

    bool BulletShooter::IsOnCooldown() const
    {
        if (m_CooldownClock.getElapsedTime().asSeconds() > m_CooldownTime)
        {
            return false;
        }

        return true;
    }

    bool BulletShooter::CanShoot() const
    {
        // should override this at some point
        return true;
    }

    void BulletShooter::ShootImpl()
    {
        m_CooldownClock.restart();
        LOG("Shooting from bullet shooter");
    }
}
