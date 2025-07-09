//
// Created by Ori Sofer on 29/03/2025.
//

#include "weapon/Bullet.h"

#include "framework/MathUtility.h"

namespace ly
{
    Bullet::Bullet(World *world, Actor *owner, const std::string &texturePath, float speed, float damage, float moveAngle)
        : Actor(world, texturePath),
        m_Owner(owner),
        m_Speed(speed),
        m_Damage(damage),
        m_MoveAngle(moveAngle)
    {
        SetTeamID(owner->GetTeamID());
        SetRotation(owner->GetRotation());
    }

    void Bullet::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true);
    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);

        if (IsActorOutOfWindowBounds(100))
        {
            Destroy();
        }
    }

    void Bullet::SetSpeed(float speed)
    {
        m_Speed = speed;
    }

    void Bullet::SetDamage(float damage)
    {
        m_Damage = damage;
    }

    void Bullet::SetMoveAngle(float moveAngle)
    {
        m_MoveAngle = moveAngle;
    }

    float Bullet::GetDamage() const
    {
        return m_Damage;
    }

    void Bullet::Move(float deltaTime)
    {
        sf::Vector2f forwardDir = m_Owner->GetForwardDirection();

        sf::Vector2f rotated = ly::RotateVector(forwardDir, m_MoveAngle);
        sf::Vector2f rotatedNormalized = ly::Normalize(rotated);
        AddActorLocationOffset(rotatedNormalized * m_Speed * deltaTime);
    }

    void Bullet::OnActorBeginOverlap(Actor *other)
    {
        if (IsOtherHostile(other))
        {
            other->ApplyDamage(GetDamage());
            Destroy();
        }
    }

    void Bullet::OnActorEndOverlap(Actor *other)
    {

    }
}
