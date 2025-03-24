//
// Created by Ori Sofer on 24/03/2025.
//

#include "weapon/Shooter.h"

namespace ly
{
    Shooter::Shooter(Actor* owner) : m_Owner{owner}
    {

    }

    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown())
        {
            ShootImpl();
        }
    }

    bool Shooter::CanShoot() const
    {
        return true;
    }

    bool Shooter::IsOnCooldown() const
    {
        return false;
    }

    Actor* Shooter::GetActor() const
    {
        return m_Owner;
    }
}
