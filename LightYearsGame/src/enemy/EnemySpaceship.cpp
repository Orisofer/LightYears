//
// Created by Ori Sofer on 03/05/2025.
//

#include "player/PlayerManager.h"
#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "reward/Reward.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage) :
    Spaceship(owningWorld, texturePath),
    m_CollisionDamage(collisionDamage),
    m_ScoreAmount(10)
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

    void EnemySpaceship::SetScoreAmount(unsigned int amount)
    {
        m_ScoreAmount = amount;
    }

    void EnemySpaceship::SetRewards()
    {
        m_RewardsMethods =
        {
            CreateHealthReward,
            CreateLifeReward,
            CreateThreeWayReward,
            CreateFrontalWiperReward
        };
    }

    void EnemySpaceship::SpawnReward()
    {
        int randomNum = (int)RandomRange(0, 100);

        if (randomNum <= 40) return;

        weak<Reward> reward;

        if (randomNum >= 41 && randomNum <= 64)
        {
            reward = m_RewardsMethods[0](m_OwningWorld);
        }

        if (randomNum >= 65 && randomNum <= 79)
        {
            reward = m_RewardsMethods[1](m_OwningWorld);
        }

        if (randomNum >= 80 && randomNum <= 92)
        {
            reward = m_RewardsMethods[2](m_OwningWorld);
        }

        if (randomNum >= 93 && randomNum <= 100)
        {
            reward = m_RewardsMethods[3](m_OwningWorld);
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
        Player* player = PlayerManager::Get().GetPlayer();

        if (player != nullptr && !player->IsPendingDestroyed())
        {
            player->AddScore(m_ScoreAmount);
        }

        SpawnReward();
    }
}
