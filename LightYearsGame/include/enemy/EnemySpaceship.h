//
// Created by Ori Sofer on 03/05/2025.
//

#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include "spaceship/Spaceship.h"
#include "reward/Reward.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);
        virtual void Tick(float deltaTime) override;
        void SetScoreAmount(unsigned int amount);
        void SetRewardSpawnWeight(float weight);

    private:
        virtual void OnActorBeginOverlap(Actor *other) override;
        virtual void Blew() override;
        void SetRewards();
        void SpawnReward();

        List<RewardFactoryFunc> m_RewardsMethods;
        float m_CollisionDamage;
        unsigned int m_ScoreAmount;
    };
}

#endif //ENEMYSPACESHIP_H
