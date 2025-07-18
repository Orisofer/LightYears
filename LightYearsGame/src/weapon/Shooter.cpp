//
// Created by Ori Sofer on 24/03/2025.
//

#include "weapon/Shooter.h"

namespace ly
{
    Shooter::Shooter(Actor* owner) : m_Owner{owner},
    m_CurrentLevel(1),
    m_MaxLevel(4)
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

    void Shooter::LevelUp(int amount)
    {
        if (amount <= 0) return;

        m_CurrentLevel += amount;

        if (m_CurrentLevel > m_MaxLevel)
        {
            m_CurrentLevel = m_MaxLevel;
        }
    }

    int Shooter::GetCurrentLevel() const
    {
        return m_CurrentLevel;
    }

    int Shooter::GetMaxLevel() const
    {
        return m_MaxLevel;
    }

    Actor * Shooter::GetOwner() const
    {
        return m_Owner;
    }
}
