//
// Created by Ori Sofer on 03/05/2025.
//

#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "reward/Reward.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage) :
    Spaceship(owningWorld, texturePath),
    m_CollisionDamage(collisionDamage)
    {
        SetTeamID(2);
        SetRewards();
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetGlobalBounds().width * 4.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SetRewards()
    {
        m_RewardsMethods =
        {
            CreateHealthReward,
            CreateThreeWayReward,
            CreateFrontalWiperReward
        };
    }

    void EnemySpaceship::SpawnReward()
    {
        int randomNum = (int)RandomRange(0, 100);

        if (randomNum <= 40) return;

        weak<Reward> reward;

        if (randomNum >= 41 && randomNum <= 70)
        {
            reward = m_RewardsMethods[0](m_OwningWorld);
        }

        if (randomNum >= 71 && randomNum <= 90)
        {
            reward = m_RewardsMethods[1](m_OwningWorld);
        }

        if (randomNum >= 91 && randomNum <= 100)
        {
            reward = m_RewardsMethods[2](m_OwningWorld);
        }

        reward.lock()->SetLocation(GetLocation());
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        Spaceship::OnActorBeginOverlap(other);

        if (IsOtherHostile(other))
        {
            other->ApplyDamage(m_CollisionDamage);
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
    }
}
