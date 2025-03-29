//
// Created by Ori Sofer on 24/03/2025.
//

#include "weapon/BulletShooter.h"

#include "framework/MathUtility.h"
#include "framework/World.h"
#include "weapon/Bullet.h"

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
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetLocation());
        newBullet.lock()->SetActorRotation(ly::DegreesToRadians(0.f));
    }
}
