//
// Created by Ori Sofer on 03/05/2025.
//

#include "enemy/EnemySpaceship.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage) :
    Spaceship(owningWorld, texturePath),
    m_CollisionDamage(collisionDamage)
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetGlobalBounds().width * 4.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        Spaceship::OnActorBeginOverlap(other);

        if (IsOtherHostile(other))
        {
            other->ApplyDamage(m_CollisionDamage);
        }
    }
}
