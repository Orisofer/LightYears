//
// Created by Ori Sofer on 24/03/2025.
//

#include "weapon/BulletShooter.h"

#include "framework/MathUtility.h"
#include "framework/World.h"
#include "weapon/Bullet.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor *owner, float coolDownTime, const sf::Vector2f& localPositionOffset,
            float localRotationOffset, const std::string& texturePath) : Shooter{owner},
    m_CooldownClock{},
    m_TexturePath(texturePath),
    m_CooldownTime{coolDownTime},
    m_LocalPositionOffset(localPositionOffset),
    m_LocalRotationOffset(localRotationOffset)
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
        sf::Vector2f ownerForwardDir = GetOwner()->GetForwardDirection();
        sf::Vector2f ownerRightDir = GetOwner()->GetRightDirection();

        sf::Vector2f yOffset = ownerForwardDir * m_LocalPositionOffset.y;
        sf::Vector2f xOffset = ownerRightDir * m_LocalPositionOffset.x;

        sf::Vector2f finalPosOffset = xOffset + yOffset;

        m_CooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), m_TexturePath);
        newBullet.lock()->SetLocation(GetOwner()->GetLocation() + finalPosOffset);
        newBullet.lock()->SetRotation(GetOwner()->GetRotation() + m_LocalRotationOffset);
    }
}
