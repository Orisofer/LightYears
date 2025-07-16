//
// Created by Ori Sofer on 15/07/2025.
//

#include "reward/Reward.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiperShooter.h"

namespace ly
{
    Reward::Reward(World *owningWorld, const std::string &texturePath, RewardFunc rewardFunc, float speed)
        : Actor(owningWorld, texturePath),
    m_Speed(speed),
    m_RewardFunc(rewardFunc)

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

        AddActorLocationOffset(downWards * m_Speed * deltaTime);
    }

    void Reward::OnActorBeginOverlap(Actor *other)
    {
        // todo: clean up casting in the future
        PlayerSpaceship* player = dynamic_cast<PlayerSpaceship*>(other);

        if (player != nullptr && !player->IsPendingDestroyed())
        {
            m_RewardFunc(player);
            Destroy();
        }
    }

    void Reward::OnActorEndOverlap(Actor *other)
    {

    }

    // -------------------- REWARDS FACTORY ---------------------

    weak<Reward> CreateReward(World *world, const std::string &texturePath, RewardFunc rewardFunc, float speed)
    {
        weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc, speed);
        return reward;
    }

    weak<Reward> CreateHealthReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
    }

    weak<Reward> CreateThreeWayReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/things_bronze.png", RewardThreeWayShooter);
    }

    weak<Reward> CreateFrontalWiperReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/bolt_gold.png", RewardFrontalWiperShooter);
    }

    void RewardHealth(PlayerSpaceship *player)
    {
        static float rewardAmount = 10.f;

        if (player != nullptr && !player->IsPendingDestroyed())
        {
            player->GetHealthComponent().ChangeHealth(rewardAmount);
        }
    }

    void RewardThreeWayShooter(PlayerSpaceship *player)
    {
        if (player != nullptr && !player->IsPendingDestroyed())
        {
            player->SetShooter(unique<Shooter>{new ThreeWayShooter(player, 0.12f, {0.f, 50.f})});
        }
    }

    void RewardFrontalWiperShooter(PlayerSpaceship *player)
    {
        if (player != nullptr && !player->IsPendingDestroyed())
        {
            player->SetShooter(unique<Shooter>{new FrontalWiperShooter(player, 0.12f, {0.f, 50.f})});
        }
    }

    // -------------------------------------------------------
}
