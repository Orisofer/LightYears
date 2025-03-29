//
// Created by Ori Sofer on 29/03/2025.
//

#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(World *world, Actor *owner, const std::string &texturePath, float speed, float damage)
        : Actor(world, texturePath),
        m_Owner(owner),
        m_Speed(speed),
        m_Damage(damage)
    {

    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
    }

    void Bullet::SetSpeed(float speed)
    {
        m_Speed = speed;
    }

    void Bullet::SetDamage(float damage)
    {
        m_Damage = damage;
    }

    void Bullet::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * m_Speed * deltaTime);
    }
}
