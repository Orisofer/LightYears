//
// Created by Ori Sofer on 15/07/2025.
//

#include "reward/Reward.h"
#include "framework/MathUtility.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Reward::Reward(World *owningWorld, const std::string &texturePath, RewardFunc rewardFunc, float speed)
        : Actor(owningWorld, texturePath),
    m_RewardFunc(rewardFunc),
    m_Speed(speed)
    {

    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true);
    }

    void Reward::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        sf::Vector2f currentPos = GetLocation();
        sf::Vector2f downWards = sf::Vector2f(0, 1);
        sf::Vector2f dir = downWards - currentPos;

        Normalize(dir);

        SetLocation(dir * m_Speed * deltaTime);
    }

    void Reward::OnActorBeginOverlap(Actor *other)
    {
        // todo: clean up casting in the future
        PlayerSpaceship* player = static_cast<PlayerSpaceship*>(other);

        if (player != nullptr && !player->IsPendingDestroyed())
        {
            m_RewardFunc(player);
        }
    }

    void Reward::OnActorEndOverlap(Actor *other)
    {

    }
}
